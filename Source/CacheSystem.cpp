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
{

}

CacheSystem::~CacheSystem()
{

}

bool CacheSystem::connectToServer()
{
	// initialise
	MYSQL *con = mysql_init(NULL);

	if (con == NULL)
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		return false;
	}

	// connect
	if (mysql_real_connect(con, "localhost", "root", "k41n0ur10p4ss",
		NULL, 0, NULL, 0) == NULL)
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		return false;
	}

	// select db
	if (mysql_query(con, "USE com_coeus"))
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		return false;
	}

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
	// store results to process later
	// unlock
}

int CacheSystem::fetchResultsFor(String &str)
{
	// lock
	// get request
	// unlock

	// process request
	// post message

	return 0;
}