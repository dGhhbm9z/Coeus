#include "CacheSystem.h"
#include <mysql.h>

CacheSystem* CacheSystem::instancePointer = nullptr;

CacheSystem *CacheSystem::getInstance()
{
	if (instancePointer == nullptr) {
		return (instancePointer = new CacheSystem());
	}
	else {
		return instancePointer;
	}
}

CacheSystem::CacheSystem()
: Thread("Cache System Thread")
{
	nextQueryToServeIndex = -1;
	setPassword();
	startThread();
}

CacheSystem::~CacheSystem()
{
	stopThread(10000);
}

void *CacheSystem::initialiseConnection()
{
	// initialise
	MYSQL *con = mysql_init(NULL);

	if (con == NULL)
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		return nullptr;
	}

	// connect
	if (mysql_real_connect(con, "localhost", "root", "k41n0ur10p4ss",
		NULL, 0, NULL, 0) == NULL)
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		return nullptr;
	}

	// select db
	if (mysql_query(con, "USE com_coeus"))
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		return nullptr;
	}

	return con;
/*
	// command
	String query = L"SELECT Code, Name, AccountType, XreosPist FROM accounts";

	if ( mysql_real_query(con, query.toRawUTF8(), CharPointer_UTF8::getBytesRequiredFor(query.getCharPointer())) )
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		return false;
	}

	// get results
	MYSQL_RES *result = mysql_store_result(con);

	if (result) {
		// 
		MYSQL_ROW row;
		unsigned int num_fields;
		unsigned int i;

		num_fields = mysql_num_fields(result);
		while ((row = mysql_fetch_row(result)))
		{
			unsigned long *lengths;
			lengths = mysql_fetch_lengths(result);
			for (i = 0; i < num_fields; i++)
			{
				printf("[%.*s] ", (int)lengths[i],
					row[i] ? row[i] : "NULL");
			}
			printf("\n");
		}
	}
	else {
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		return false;
	}

	// close connection
	mysql_close(con);

	return true;
*/
}

bool CacheSystem::setUserName()
{
	username = L"root";
	return true;
}

bool CacheSystem::setPassword()
{
	password = L"k41n0ur10p4ss";
	return true;
}

bool CacheSystem::setServer(String &address_, uint32 port_)
{
	address = L"localhost";
	return true;
}

void CacheSystem::getResultsFor(String &str, CacheSystemClient *client)
{
	// lock
	//ScopedLock requestLock(querySection);

	// store results to process late
	bool found = false;
	for (int i = 0; i < queries.size(); i++) {
		if (queries[i]->request == str) {
			found = true;
			queries[i]->clientList.addIfNotAlreadyThere(client);

			if (queries[i]->result != nullptr) {
				// TODO : notify newly added client
				CacheReadyMessage *msg = new CacheReadyMessage(client, queries[i]);
				msg->post();
			}

			break;
		}
	}

	if (!found) {
		QueryEntry *re = new QueryEntry();
		re->request = str;
		re->clientList.addIfNotAlreadyThere(client);
		queries.add(re);

		// notify "consumer" thread in case it is waiting
		this->notify();
	}

	// unlock
}

void CacheSystem::serveNextQuery()
{
	QueryEntry *query;
	int nextQuery;

	{
		// lock
		//ScopedLock requestLock(querySection);

		// get request
		nextQuery = nextQueryToServeIndex;
		query = [&]()->decltype(queries[nextQuery]) {
			while (++nextQuery < queries.size() &&  queries[nextQuery]->result != nullptr)  {}
			return queries[nextQuery];
		}();

		// unlock
	}

	if (query == nullptr) {
		return; // nothing to do...
	}

	// process request
	MYSQL *con = (MYSQL *) initialiseConnection();
	if (con == NULL) {
		return;
	}

	if (mysql_real_query(con, query->request.toUTF8().getAddress(), query->request.getNumBytesAsUTF8()) != 0) {
		// TODO: failure
		std::cout << "query failed" << std::endl;
		mysql_close(con);
		return;
	}
	else {
		// query succeded
		MYSQL_RES *res = mysql_store_result(con);
		if (res == NULL) {
			// TODO: failure
			fprintf(stderr, "%s\n", mysql_error(con));
			mysql_close(con);
			return;
		}

		// result size estimation and allocation
		query->size = QUERYBLOCKSIZE;
		query->result = (void *)malloc(query->size); // 2MB
		query->usedSpace = 0;
		if (query->result == nullptr) {
			// TODO : failed
			std::cout << "Allocation for results failed" << std::endl;
			mysql_close(con);
			return;
		}

		MYSQL_ROW row;
		unsigned int num_fields;
		unsigned int i;

		num_fields = mysql_num_fields(res);
		query->num_fields = num_fields;
		while ((row = mysql_fetch_row(res)))
		{
			unsigned long *lengths;
			lengths = mysql_fetch_lengths(res);

			// if needed reallocate query result buffer
			unsigned long totalRowSize = 0;
			for (i = 0; i < num_fields; i++) {
				totalRowSize += lengths[i];
			}

			if (query->usedSpace + totalRowSize > query->size) {
				unsigned long newSize = query->size +  jmax(totalRowSize, (unsigned long)QUERYBLOCKSIZE);
				void *r = realloc(query->result, newSize);
				if (r == NULL) {
					// TODO: failed
					std::cout << "Reallocation failed" << std::endl;
					return;
				}
				else {
					query->result = r;
					std::cout << "Reallocated space for results" << std::endl;
				}
			}

			// copy data
			for (i = 0; i < num_fields; i++) {
				memcpy((uint8 *)(query->result) + query->usedSpace, row[i], lengths[i]);
				query->fieldSizes.add(lengths[i]);
				query->usedSpace += lengths[i];
			}
		}

		query->num_rows = mysql_num_rows(res);

		// on sucess - update next query position
		nextQueryToServeIndex = nextQuery;
	}

	mysql_close(con);

	// post message to inform clients
	const int clsz = query->clientList.size();
	for (int i = 0; i < 1; i++) {
		CacheReadyMessage *msg = new CacheReadyMessage(query->clientList[i], query);
		msg->post();
	}

}

bool CacheSystem::hasUnservedQueries() const
{
	for (auto q = queries.begin(); q != queries.end(); ++q) {
		if ((*q)->result == nullptr) {
			return true;
		}
	}

	return false;
}

void CacheSystem::run() {
	while (1) {

		if (threadShouldExit()) {
			return;
		}
		else if (hasUnservedQueries()) {
			serveNextQuery();
		}

		Thread::wait(500);
	}
}
