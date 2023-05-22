#include "../include/MySQLBank.h"
#include <fstream>

uint8_t MySQLBank::connect(const std::string& path_to_ticket)
{
	std::string server;
	std::string username;
	std::string password;

	std::ifstream fin(path_to_ticket);
	if (!fin.is_open())
	{
		printf("\"%s\" isn't exist\n", path_to_ticket.c_str());
		return ERR_NO_KEY;
	}

	std::getline(fin, server);
	std::getline(fin, username);
	std::getline(fin, password);

	fin.close();

	try
	{
		mDriver = get_driver_instance();
		mConnection = mDriver->connect(server, username, password);
		return 0;
	}
	catch (const sql::SQLException e)
	{
		printf("Server Error: %s\n", e.what());
		return ERR_CONNECTION;
	}
}

void MySQLBank::selectDataBase(const std::string& name_db)
{
	mConnection->setSchema(name_db);
}

bool MySQLBank::immediatelyExecute(const std::string& query)
{
	mStatement = mConnection->createStatement();
	return mStatement->execute(query);
}

void MySQLBank::prepareExecution(const std::string& query)
{
	mPreparedStatement = mConnection->prepareStatement(query);
}

bool MySQLBank::executeQuery(const std::string& query)
{
	mStatement = mConnection->createStatement();
	mResult = mStatement->executeQuery(query);
	return mResult;
}

void MySQLBank::executeUpdate(const std::string query)
{
	mStatement = mConnection->createStatement();
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

MySQLBank::~MySQLBank()
{
	mConnection->close();
	delete mConnection;
	delete mStatement;
	delete mPreparedStatement;
	delete mResult;

}
