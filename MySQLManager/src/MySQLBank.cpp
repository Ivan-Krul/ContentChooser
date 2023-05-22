#include "../include/MySQLBank.h"
#include <fstream>

bool MySQLBank::connect(const std::string& path_to_ticket)
{
	std::string server;
	std::string username;
	std::string password;

	std::ifstream fin(path_to_ticket);
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

	try
	{
		mDriver.reset(get_driver_instance());
		mConnection.reset(mDriver->connect(server, username, password));
		return true;
	}
	catch (const sql::SQLException e)
	{
		printf("Server Error: %s\n", e.what());
		return false;
	}
}

void MySQLBank::selectDataBase(const std::string& name_db)
{
	mConnection->setSchema(name_db);
}

bool MySQLBank::immediatelyExecute(const std::string& query)
{
	mStatement.reset(mConnection->createStatement());
	return mStatement->execute(query);
}

void MySQLBank::prepareExecution(const std::string& query)
{
	mPreparedStatement.reset(mConnection->prepareStatement(query));
}

bool MySQLBank::executeQuery(const std::string& query)
{
	mStatement.reset(mConnection->createStatement());
	mResult.reset(mStatement->executeQuery(query));
	return mResult.get();
}

void MySQLBank::executeUpdate(const std::string query)
{
	mStatement.reset(mConnection->createStatement());
	mStatement->executeUpdate(query);
}

bool MySQLBank::executePrepared()
{
	return mPreparedStatement->execute();
}

size_t MySQLBank::getResultColomns()
{
	sql::ResultSetMetaData* res_meta = mResult->getMetaData();
	size_t columns = res_meta->getColumnCount();
	return columns;
}
