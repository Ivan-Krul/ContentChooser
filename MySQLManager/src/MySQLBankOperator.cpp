#include "../include/MySQLBank.h"
#include <fstream>
#include <exception>
#include <stdlib.h>

void MySQLBankOperator::readFromTicket(const std::string& path_to_ticket)
{
	std::ifstream fin(path_to_ticket);
	if (!fin.is_open())
		throw std::domain_error("the file isn't found");

	std::getline(fin, mServerPath);
	std::getline(fin, mServerUser);
	std::getline(fin, mServerPass);

	fin.close();
}

void MySQLBankOperator::connectOper()
{
	try
	{
		mDriver = get_driver_instance();
		mConnection = mDriver->connect(mServerPath, mServerUser, mServerPass);
	}
	catch (const sql::SQLException& e)
	{
		throw e;
	}
}

void MySQLBankOperator::selectSchemeOper(const std::string& name_db)
{
	try
	{
		mConnection->setSchema(name_db);
	}
	catch (sql::SQLException& e)
	{
		throw e;
	}
}

bool MySQLBankOperator::immediatelyExecuteOper(const std::string& query)
{
	try
	{
		mStatement = mConnection->createStatement();
		return mStatement->execute(query);
	}
	catch (sql::SQLException& e)
	{
		throw e;
	}
}

void MySQLBankOperator::prepareExecutionOper(const std::string& query)
{
	try
	{
		mPreparedStatement = mConnection->prepareStatement(query);
	}
	catch (sql::SQLException& e)
	{
		throw e;
	}
}

bool MySQLBankOperator::executePreparedOper()
{
	try
	{
		mPreparedStatement->execute();
		return true;
	}
	catch (sql::SQLException& e)
	{
		throw e;
	}
}

bool MySQLBankOperator::executeQueryOper(const std::string& query)
{
	try
	{
		mStatement = mConnection->createStatement();
		mResult = mStatement->executeQuery(query);
		return mResult;
	}
	catch (sql::SQLException& e)
	{
		throw e;
	}
}

int MySQLBankOperator::executeUpdateOper(const std::string& query)
{
	try
	{
		mStatement = mConnection->createStatement();
		int res = mStatement->executeUpdate(query);
		return res;
	}
	catch (sql::SQLException& e)
	{
		throw e;
	}
}
