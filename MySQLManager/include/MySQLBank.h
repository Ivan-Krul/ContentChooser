#pragma once
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory>
#include <mysql/jdbc.h>

struct IMySQLBank
{
	virtual bool connect(const std::string& path_to_ticket) = 0;

	virtual void selectDataBase(const std::string& name_db) = 0;

	virtual bool immediatelyExecute(const std::string& query) = 0;
	virtual void prepareExecution(const std::string& query) = 0;
	virtual bool executePrepared() = 0;
	virtual bool executeQuery(const std::string& query) = 0;
	virtual void executeUpdate(const std::string query) = 0;

	virtual size_t getResultColomns() = 0;

	virtual std::auto_ptr<sql::Driver>& getDriverInstance() = 0;
	virtual std::auto_ptr<sql::Connection>& getConnectionInstance() = 0;
	virtual std::auto_ptr<sql::Statement>& getStatementInstance() = 0;
	virtual std::auto_ptr<sql::PreparedStatement>& getPreparedStatementInstance() = 0;
	virtual std::auto_ptr<sql::ResultSet>& getResultInstance() = 0;
};

class MySQLBank : public IMySQLBank
{
public:
	bool connect(const std::string& path_to_ticket) override;

	void selectDataBase(const std::string& name_db) override;

	bool immediatelyExecute(const std::string& query) override;
	void prepareExecution(const std::string& query) override;
	bool executePrepared() override;
	bool executeQuery(const std::string& query) override;
	void executeUpdate(const std::string query) override;

	size_t getResultColomns() override;

	inline std::auto_ptr<sql::Driver>& getDriverInstance() override { return mDriver; };
	inline std::auto_ptr<sql::Connection>& getConnectionInstance() override { return mConnection; };
	inline std::auto_ptr<sql::Statement>& getStatementInstance() override { return mStatement; };
	inline std::auto_ptr<sql::PreparedStatement>& getPreparedStatementInstance() override { return mPreparedStatement; };
	inline std::auto_ptr<sql::ResultSet>& getResultInstance() override { return mResult; };
private:
	std::auto_ptr<sql::Driver> mDriver; // sql drivers for further connection
	std::auto_ptr<sql::Connection> mConnection; // connection statement itself
	std::auto_ptr<sql::Statement> mStatement; // instance statement of db (execute management of databases or table configurations)
	std::auto_ptr<sql::PreparedStatement> mPreparedStatement; // prepared statement of db (execute queries)
	std::auto_ptr<sql::ResultSet> mResult; // result of query
};

