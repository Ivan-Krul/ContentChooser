#include "../include/MySQLBank.h"
#include <fstream>
#include <exception>

template class MySQLBank<false>;
template class MySQLBank<true>;

template<bool _Exception>
uint8_t MySQLBank<_Exception>::connect(const std::string& path_to_ticket)
{
	std::string server;
	std::string username;
	std::string password;

	std::ifstream fin(path_to_ticket);
	if (!fin.is_open())
	{
		if (_Exception)
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
		if (_Exception)
			throw e;
		else
		{
			printf("Server Error: %s\n", e.what());
			return ERR_CONNECTION;
		}
	}
}

template<bool _Exception>
void MySQLBank<_Exception>::selectScheme(const std::string& name_db)
{
	mConnection->setSchema(name_db);
}

template<bool _Exception>
bool MySQLBank<_Exception>::immediatelyExecute(const std::string& query)
{
	try
	{
		mStatement = mConnection->createStatement();
		return mStatement->execute(query);
	}
	catch (sql::SQLException& e)
	{
		if (_Exception)
			throw e;
		else
		{
			printf("Query Error: %s\n", e.what());
			return false;
		}
	}
}

template<bool _Exception>
void MySQLBank<_Exception>::prepareExecution(const std::string& query)
{
	try
	{
		mPreparedStatement = mConnection->prepareStatement(query);
	}
	catch (sql::SQLException& e)
	{
		if (_Exception)
			throw e;
		else
			printf("Query Error: %s\n", e.what());
	}
}

template<bool _Exception>
bool MySQLBank<_Exception>::executeQuery(const std::string& query)
{
	try
	{
		mStatement = mConnection->createStatement();
		mResult = mStatement->executeQuery(query);
		return mResult;
	}
	catch (sql::SQLException& e)
	{
		if (_Exception)
			throw e;
		else
		{
			printf("Query Error: %s\n", e.what());
			return false;
		}
	}
}

template<bool _Exception>
void MySQLBank<_Exception>::executeUpdate(const std::string query)
{
	try
	{
		mStatement = mConnection->createStatement();
		mStatement->executeUpdate(query);
	}
	catch (sql::SQLException& e)
	{
		if (_Exception)
			throw e;
		else
			printf("Update Error: %s\n", e.what());
	}
}

template<bool _Exception>
bool MySQLBank<_Exception>::executePrepared()
{
	try
	{
		return mPreparedStatement->execute();
	}
	catch (sql::SQLException& e)
	{
		if (_Exception)
			throw e;
		else
		{
			printf("Update Error: %s\n", e.what());
			return false;
		}
	}
}

template<bool _Exception>
size_t MySQLBank<_Exception>::getResultColomns()
{
	sql::ResultSetMetaData* res_meta = mResult->getMetaData();
	size_t columns = res_meta->getColumnCount();
	return columns;
}

template<bool _Exception>
MySQLBank<_Exception>::~MySQLBank()
{
	mConnection->close();
	delete mConnection;
	delete mStatement;
	delete mPreparedStatement;
	delete mResult;

}
