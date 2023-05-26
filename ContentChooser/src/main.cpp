#include <stdlib.h>
#include <iostream>
#include <fstream>

#include <mysql/jdbc.h>

#include "MySQLBank.h"

int main()
{
	MySQLBank bank;
	if (bank.connect("../resource/dbticket.txt") != 0)
	{
		printf("No connection or no key");
		exit(1);
	}
	bank.immediatelyExecute("DROP DATABASE IF EXISTS content_chooser;");
	bank.immediatelyExecute("CREATE DATABASE content_chooser;");
	bank.selectScheme("content_chooser");
	printf("deleted and created database\n");

	bank.immediatelyExecute("CREATE TABLE content_name(id serial PRIMARY KEY, title varchar(128), duration_m smallint unsigned);");
	printf("created table\n");

	bank.prepareExecution("INSERT INTO content_name(title, duration_m) VALUES(?, ?)");
	bank.getPreparedStatementInstance()->setString(1,"Star versus the Forces of Evil");
	bank.getPreparedStatementInstance()->setInt(2, 22);
	bank.executePrepared();
	printf("executed\n");

	bank.getPreparedStatementInstance()->setString(1, "Amphibia");
	bank.getPreparedStatementInstance()->setInt(2, 23);
	bank.executePrepared();
	printf("executed\n");

	bank.executeQuery("SELECT * FROM content_name");
	printf("got\n");

	size_t col = bank.getResultColomns();
	auto res = bank.getResultInstance();
	printf("prepared\n");

	while (res->next())
	{
		for (size_t i = 1; i <= col; i++)
			std::cout << res->getString(i) << '\t';

		std::cout << "\n";
	}

	return 0;
}
