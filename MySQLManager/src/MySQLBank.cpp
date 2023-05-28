#include "../include/MySQLBank.h"

MySQLBankBase::~MySQLBankBase()
{
	mConnection->close();
	delete mConnection;
	delete mStatement;
	delete mPreparedStatement;
	delete mResult;
}

uint8_t MySQLBankUnSafe::connect(const std::string& path_to_ticket)
{
	try
	{
		readFromTicket(path_to_ticket);
	}
	catch (const std::exception& e)
	{
		throw e;
	}

	try
	{
		connectOper();
	}
	catch (const sql::SQLException& e)
	{
		throw e;
	}
	return 0;
}

bool MySQLBankUnSafe::selectScheme(const std::string& name_db)
{
	try
	{
		selectSchemeOper(name_db);
	}
	catch (sql::SQLException& e)
	{
		throw e;
	}
	return true;
}

bool MySQLBankUnSafe::immediatelyExecute(const std::string& query)
{
	try
	{
		bool res = immediatelyExecuteOper(query);
		return res;
	}
	catch (sql::SQLException& e)
	{
		throw e;
	}
	return true;
}

void MySQLBankUnSafe::prepareExecution(const std::string& query)
{
	try
	{
		prepareExecutionOper(query);
	}
	catch (sql::SQLException& e)
	{
		throw e;
	}
}

bool MySQLBankUnSafe::executePrepared()
{
	try
	{
		bool res = executePreparedOper();
		return res;
	}
	catch (sql::SQLException& e)
	{
		throw e;
	}
}

bool MySQLBankUnSafe::executeQuery(const std::string& query)
{
	try
	{
		bool res = executeQueryOper(query);
		return res;
	}
	catch (sql::SQLException& e)
	{
		throw e;
	}
}

int MySQLBankUnSafe::executeUpdate(const std::string& query)
{
	try
	{
		int res = executeUpdateOper(query);
		return res;
	}
	catch (sql::SQLException& e)
	{
		throw e;
	}
}

size_t MySQLBankUnSafe::getResultColomns()
{
	sql::ResultSetMetaData* res_meta = mResult->getMetaData();
	size_t columns = res_meta->getColumnCount();
	return columns;
}

uint8_t MySQLBankSafe::connect(const std::string& path_to_ticket) noexcept
{
	try
	{
		readFromTicket(path_to_ticket);
	}
	catch (const std::exception& e)
	{
		printf("Error connection: %s\n", e.what());
		return ERR_NO_KEY;
	}

	try
	{
		connectOper();
	}
	catch (const sql::SQLException& e)
	{
		printf("Error SQL connection: %s\n", e.what());
		return ERR_CONNECTION;
	}
	return 0;
}

bool MySQLBankSafe::selectScheme(const std::string& name_db) noexcept
{
	try
	{
		selectSchemeOper(name_db);
	}
	catch (sql::SQLException& e)
	{
		printf("Error SQL selection: %s\n", e.what());
		return false;
	}
	return true;
}

bool MySQLBankSafe::immediatelyExecute(const std::string& query) noexcept
{
	try
	{
		bool res = immediatelyExecuteOper(query);
		return res;
	}
	catch (sql::SQLException& e)
	{
		printf("Error SQL execution: %s\n", e.what());
		return false;
	}
}

void MySQLBankSafe::prepareExecution(const std::string& query) noexcept
{
	try
	{
		prepareExecutionOper(query);
	}
	catch (sql::SQLException& e)
	{
		printf("Error SQL preperation: %s\n", e.what());
		return;
	}
}

bool MySQLBankSafe::executePrepared() noexcept
{
	try
	{
		bool res = executePreparedOper();
		return res;
	}
	catch (sql::SQLException& e)
	{
		printf("Error SQL execution: %s\n", e.what());
		return false;
	}
}

bool MySQLBankSafe::executeQuery(const std::string& query) noexcept
{
	try
	{
		bool res = executeQueryOper(query);
		return res;
	}
	catch (sql::SQLException& e)
	{
		printf("Error SQL execution: %s\n", e.what());
		return false;
	}
}

int MySQLBankSafe::executeUpdate(const std::string& query) noexcept
{
	try
	{
		int res = executeUpdateOper(query);
		return res;
	}
	catch (sql::SQLException& e)
	{
		printf("Error SQL execution: %s\n", e.what());
		return false;
	}
}

size_t MySQLBankSafe::getResultColomns() noexcept
{
	sql::ResultSetMetaData* res_meta = mResult->getMetaData();
	size_t columns = res_meta->getColumnCount();
	return columns;
}
