#include "CacheSystem.h"
#include <mysql.h>

CacheSystem::CacheSystem()
{

}

CacheSystem::~CacheSystem()
{

}

MYSQL *CacheSystem::initialiseConnection()
{
	MYSQL *con = mysql_init(NULL);

	if (con == NULL)
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		return nullptr;
	}

	if (mysql_real_connect(con, "localhost", "root", "k41n0ur10p4ss",
		NULL, 0, NULL, 0) == NULL)
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		return nullptr;
	}

	if (mysql_query(con, "USE com_coeus"))
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		return nullptr;
	}

	return con;
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
			}

			break;
		}
	}

	if (!found) {
		QueryEntry *re = new QueryEntry();
		re->request = str;
		queries.add(re);
	}
	// unlock
}

void CacheSystem::serveNextQuery()
{
	QueryEntry *query;

	{
		// lock
		//ScopedLock requestLock(querySection);

		// get request
		query = queries[0];

		// unlock
	}

	// process request
	MYSQL *con = initialiseConnection();
	if (con == NULL) {
		return;
	}

	if (mysql_real_query(con, query->request.toUTF8().getAddress(), query->request.getNumBytesAsUTF8()) != 0) {
		// TODO: failure
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
		if (query->result == NULL) {
			// TODO : failed
			std::cout << "Allocation for results failed" << std::endl;
			mysql_close(con);
			return;
		}

		MYSQL_ROW row;
		unsigned int num_fields;
		unsigned int i;

		num_fields = mysql_num_fields(res);
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
					break;
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
			}
		}
	}


	mysql_close(con);

	// post message
	// TODO
}