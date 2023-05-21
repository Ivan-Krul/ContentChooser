#pragma once
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory>
#include <mysql/jdbc.h>

struct IMySQLBank
{
	virtual bool imitiatlyExecute(std::string query) = 0;
	virtual void prepareExecution(std::string query) = 0;
};

class MySQLBank : public IMySQLBank
{
public:
	bool imitiatlyExecute(std::string query) override;
	void prepareExecution(std::string query) override;


private:
	std::auto_ptr<sql::Driver> mDriver; // sql drivers for further connection
	std::auto_ptr<sql::Connection> mConnection; // connection statement itself
	std::auto_ptr<sql::Statement> mStatement; // instance statement of db (execute management of databases or table configurations)
	std::auto_ptr<sql::PreparedStatement> mPreparedStatement; // prepared statement of db (execute queries)
	std::auto_ptr<sql::ResultSet> mResult; // result of query
};

