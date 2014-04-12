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