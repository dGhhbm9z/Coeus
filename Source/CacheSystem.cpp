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
	startThread();
}

CacheSystem::~CacheSystem()
{
	stopThread(10000);
    //deleteAndZero(instancePointer);
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
	if (mysql_real_connect(con, "localhost", "root", password.toUTF8(),
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
}

bool CacheSystem::setUserName(String &user)
{
	username = user;
	return true;
}

bool CacheSystem::setPassword(String &pass)
{
	password = pass;
	return true;
}

bool CacheSystem::setServer(String &address_, uint32 port_)
{
	address = L"localhost";
	return true;
}

bool CacheSystem::testServer()
{
	MYSQL *con = (MYSQL *)initialiseConnection();
	if (con == nullptr) {
		return false;
	}
	
	mysql_close(con);
	return true;
}

void CacheSystem::getResultsFor(String &str, QueryEntry::QueryTable tableType, CacheSystemClient *client)
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
                queries.removeAllInstancesOf(queries[i]);
			}

			break;
		}
	}

	if (!found) {
		QueryEntry *re = new QueryEntry();
		re->request = str;
		re->clientList.addIfNotAlreadyThere(client);
        re->tableType = tableType;
		queries.add(re);

		// notify "consumer" thread in case it is waiting
		this->notify();
	}

	// unlock
}

void CacheSystem::serveNextQuery()
{
    std::cout << "serveNextQuery():" << std::endl;
	QueryEntry *query;
	int nextQuery;

	{
		// lock
		//ScopedLock requestLock(querySection);

		// get request
		nextQuery = -1;
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
        // try 3-4 times then report failure
		std::cout << "query failed" << std::endl;
        nextQueryToServeIndex = nextQuery;
		mysql_close(con);
		return;
	}
	else {
		// query succeded
		MYSQL_RES *res = mysql_store_result(con);
		if (res == NULL) {
            if(mysql_field_count(con) == 0) {
                // query does not return data
                // (it was not a SELECT)
                int resNumRows = mysql_affected_rows(con);
                query->size = sizeof(long int);
                query->result = (void *)malloc(query->size);
                *((long int *)query->result) = resNumRows;
                query->usedSpace = query->size;
                query->num_fields = 1;
                query->fieldSizes.add(query->size);
                query->num_rows = 1;
            }
            else {
                // TODO: failure
                fprintf(stderr, "%s\n", mysql_error(con));
            }

            nextQueryToServeIndex = nextQuery;
		}
        else {
            // result size estimation and allocation
            query->size = QUERYBLOCKSIZE;
            query->result = (void *)malloc(query->size); // 2MB
            query->usedSpace = 0;
            if (query->result == nullptr) {
                // TODO : failed
                std::cout << "Allocation for results failed" << std::endl;
                nextQueryToServeIndex = nextQuery;
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
        }

        // update next query position
		nextQueryToServeIndex = nextQuery;
	}

	mysql_close(con);

	// post message to inform clients
	const int clsz = query->clientList.size();
	for (int i = 0; i < 1; i++) {
		CacheReadyMessage *msg = new CacheReadyMessage(query->clientList[i], query);
		msg->post();
	}
    queries.removeAllInstancesOf(query);
}

bool CacheSystem::hasUnservedQueries() const
{
	return queries.size() != 0;
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
