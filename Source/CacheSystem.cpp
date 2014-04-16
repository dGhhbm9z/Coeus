#include "CacheSystem.h"
#include <mysql.h>

CacheSystem::CacheSystem()
{

}

CacheSystem::~CacheSystem()
{

}

bool CacheSystem::connectToServer()
{
	MYSQL *con = mysql_init(NULL);

	if (con == NULL)
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		return false;
	}

	if (mysql_real_connect(con, "localhost", "root", "k41n0ur10p4ss",
		NULL, 0, NULL, 0) == NULL)
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		return false;
	}

	if (mysql_query(con, "USE com_coeus"))
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		return false;
	}

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