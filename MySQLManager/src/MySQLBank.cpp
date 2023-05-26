#include "../include/MySQLBank.h"
#include <fstream>
#include <exception>

#include <stdlib.h>

uint8_t MySQLBankUnSafe::connect(const std::string& path_to_ticket)
{
	std::string server;
	std::string username;
	std::string password;

	std::ifstream fin(path_to_ticket);
	if (!fin.is_open())
	{
		if (except)
			throw std::domain_error("the file isn't found");
		else
		{
			printf("\"%s\" isn't exist\n", path_to_ticket.c_str());
			return ERR_NO_KEY;
		}
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
		if (except)
			throw e;
		else
		{
			printf("Server Error: %s\n", e.what());
			return ERR_CONNECTION;
		}
	}
}

bool MySQLBankUnSafe::selectScheme(const std::string& name_db)
{
	try
	{
		mConnection->setSchema(name_db);
		return true;
	}
	catch (sql::SQLException& e)
	{
		if (except)
			throw e;
		else
		{
			printf("Query Error: %s\n", e.what());
			return false;
		}
	}
}

bool MySQLBankUnSafe::immediatelyExecute(const std::string& query)
{
	try
	{
		mStatement = mConnection->createStatement();
		return mStatement->execute(query);
	}
	catch (sql::SQLException& e)
	{
		if (except)
			throw e;
		else
		{
			printf("Query Error: %s\n", e.what());
			return false;
		}
	}
}

void MySQLBankUnSafe::prepareExecution(const std::string& query)
{
	try
	{
		mPreparedStatement = mConnection->prepareStatement(query);
	}
	catch (sql::SQLException& e)
	{
		if (except)
			throw e;
		else
			printf("Query Error: %s\n", e.what());
	}
}

bool MySQLBankUnSafe::executeQuery(const std::string& query)
{
	try
	{
		mStatement = mConnection->createStatement();
		mResult = mStatement->executeQuery(query);
		return mResult;
	}
	catch (sql::SQLException& e)
	{
		if (except)
			throw e;
		else
		{
			printf("Query Error: %s\n", e.what());
			return false;
		}
	}
}

void MySQLBankUnSafe::executeUpdate(const std::string query)
{
	try
	{
		mStatement = mConnection->createStatement();
		mStatement->executeUpdate(query);
	}
	catch (sql::SQLException& e)
	{
		if (except)
			throw e;
		else
			printf("Update Error: %s\n", e.what());
	}
}

bool MySQLBankUnSafe::executePrepared()
{
	try
	{
		return mPreparedStatement->execute();
	}
	catch (sql::SQLException& e)
	{
		if (except)
			throw e;
		else
		{
			printf("Update Error: %s\n", e.what());
			return false;
		}
	}
}

size_t MySQLBankUnSafe::getResultColomns()
{
	sql::ResultSetMetaData* res_meta = mResult->getMetaData();
	size_t columns = res_meta->getColumnCount();
	return columns;
}

MySQLBankBase::~MySQLBankBase()
{
	mConnection->close();
	delete mConnection;
	delete mStatement;
	delete mPreparedStatement;
	delete mResult;
}

uint8_t MySQLBankSafe::connect(const std::string& path_to_ticket) noexcept
{
	return 0;
}

bool MySQLBankSafe::selectScheme(const std::string& name_db) noexcept
{
	return false;
}

bool MySQLBankSafe::immediatelyExecute(const std::string& query) noexcept
{
	return false;
}

void MySQLBankSafe::prepareExecution(const std::string& query) noexcept
{
}

bool MySQLBankSafe::executePrepared()
{
	return false;
}

bool MySQLBankSafe::executeQuery(const std::string& query) noexcept
{
	return false;
}

void MySQLBankSafe::executeUpdate(const std::string query) noexcept
{
}

size_t MySQLBankSafe::getResultColomns() noexcept
{
	return size_t();
}
