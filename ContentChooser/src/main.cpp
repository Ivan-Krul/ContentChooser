#include <stdlib.h>
#include <iostream>
#include <fstream>

#include <mysql/jdbc.h>

#include "MySQLBank.h"

#include <vector>
/*
int main()
{
	//for demonstration only. never save your password in the code!
	std::string server;
	std::string username;
	std::string password;

	std::ifstream fin("../resource/dbticket.txt");
	if (!fin.is_open())
	{
		std::cout << "\"dbticket.txt\" isn't exist\n";
		system("pause");
		exit(1);
	}

	std::getline(fin, server);
	std::getline(fin, username);
	std::getline(fin, password);

	fin.close();

	sql::Driver* driver; // sql drivers for further connection
	sql::Connection* con; // connection statement itself
	sql::Statement* stmt; // instance statement of db (execute management of databases or table configurations)
	sql::PreparedStatement* pstmt; // prepared statement of db (execute queries)
	sql::ResultSet* res; // result of query

	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
	}
	catch (sql::SQLException e)
	{
		std::cout << "Could not connect to server. Error message: " << e.what() << '\n';
		system("pause");
		exit(1);
	}

	//please create database "quickstartdb" ahead of time
	stmt = con->createStatement();
	stmt->execute("CREATE DATABASE quickstartdb");

	con->setSchema("quickstartdb"); // select schema (database)

	
	stmt->execute("DROP TABLE IF EXISTS inventory");
	std::cout << "Finished dropping table (if existed)" << '\n';
	stmt->execute("CREATE TABLE inventory (id serial PRIMARY KEY, name VARCHAR(50), quantity INTEGER);");
	std::cout << "Finished creating table" << '\n';


	pstmt = con->prepareStatement("INSERT INTO inventory(name, quantity) VALUES(?,?)"); // questions marks is filling not imidiatly (like templates for further queries)
	pstmt->setString(1, "banana");
	pstmt->setInt(2, 150);
	pstmt->execute(); // execution
	std::cout << "One row inserted." << '\n';

	pstmt->setString(1, "orange");
	pstmt->setInt(2, 154);
	pstmt->execute();
	std::cout << "One row inserted." << '\n';

	pstmt->setString(1, "apple");
	pstmt->setInt(2, 100);
	pstmt->execute();
	std::cout << "One row inserted." << '\n';

	stmt->execute("DROP DATABASE quickstartdb");
	std::cout << "Deleted unnecessary db\n";
	
	// go to world db for testing
	con->setSchema("sakila");
	std::cout << "Select db \"sakila\"\n";

	// get cities
	stmt = con->createStatement();
	res = stmt->executeQuery("SELECT first_name, last_name FROM actor ORDER BY last_name ASC");
	//res = stmt->executeQuery("SELECT * FROM city WHERE CountryCode LIKE \"UKR\" AND Population > 500000 ORDER BY Population DESC");
	std::cout << "Got data\n";
	
	//get result set metadata
	sql::ResultSetMetaData* res_meta = res->getMetaData();
	int columns = res_meta->getColumnCount();
	std::cout << "Got metadata\n";
	std::cout << "Output\n";

	std::cout << '\n';

	//Loop for each row
	while (res->next()) {
		/* Access column data by index, 1-indexed
		for (int i = 1; i <= columns; i++) {
			std::cout << res->getString(i) << "\t|";
		}
		std::cout << '\n';

		std::cout << res->getString(2) << " ";
		std::cout << res->getString(1) << "\n";
		//std::cout << res->getString(5) << '\n';
	}

	std::cout << '\n';

	con->close();

	delete pstmt;
	delete con;
	delete stmt;
	delete res;
	system("pause");
	return 0;
}
*/
int main()
{
	MySQLBank<true> bank;
	if (bank.connect("../resource/dbticket.txt") != 0)
	{
		printf("No connection or no key");
		exit(1);
	}
	bank.immediatelyExecute("DROP DATABASE IF EXISTS content_chooser;");
	bank.immediatelyExecute("CREATE DATABASE content_chooser;");
	bank.selectScheme("content_chooser");

	bank.immediatelyExecute("CREATE TABLE name(id serial PRIMARY KEY, title varchar(128));");

	bank.prepareExecution("INSERT INTO name(title) VALUES(?)");
	bank.getPreparedStatementInstance()->setString(1,"Star versus the Forces of Evil");
	bank.executePrepared();

	bank.getPreparedStatementInstance()->setString(1, "Amphibia");
	bank.executePrepared();

	return 0;
}
