#pragma once
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory>
#include <mysql/jdbc.h>

#define ERR_CONNECTION 1
#define ERR_NO_KEY 2

struct IMySQLBank
{
	virtual uint8_t connect(const std::string& path_to_ticket) = 0;

	virtual void selectScheme(const std::string& name_db) = 0;

	virtual bool immediatelyExecute(const std::string& query) = 0;
	virtual void prepareExecution(const std::string& query) = 0;
	virtual bool executePrepared() = 0;
	virtual bool executeQuery(const std::string& query) = 0;
	virtual void executeUpdate(const std::string query) = 0;

	virtual size_t getResultColomns() = 0;

	virtual sql::Driver* getDriverInstance() = 0;
	virtual sql::Connection* getConnectionInstance() = 0;
	virtual sql::Statement*	getStatementInstance() = 0;
	virtual sql::PreparedStatement* getPreparedStatementInstance() = 0;
	virtual sql::ResultSet* getResultInstance() = 0;
};

class MySQLBank : public IMySQLBank
{
public:
	uint8_t connect(const std::string& path_to_ticket) override;

	void selectScheme(const std::string& name_db) override;

	bool immediatelyExecute(const std::string& query) override;
	void prepareExecution(const std::string& query) override;
	bool executePrepared() override;
	bool executeQuery(const std::string& query) override;
	void executeUpdate(const std::string query) override;

	size_t getResultColomns() override;

	inline sql::Driver* getDriverInstance() override { return mDriver; };
	inline sql::Connection* getConnectionInstance() override { return mConnection; };
	inline sql::Statement* getStatementInstance() override { return mStatement; };
	inline sql::PreparedStatement* getPreparedStatementInstance() override { return mPreparedStatement; };
	inline sql::ResultSet* getResultInstance() override { return mResult; };

	virtual ~MySQLBank();
private:
	sql::Driver*			mDriver; // sql drivers for further connection
	sql::Connection*		mConnection; // connection statement itself
	sql::Statement*			mStatement; // instance statement of db (execute management of databases or table configurations)
	sql::PreparedStatement*	mPreparedStatement; // prepared statement of db (execute queries)
	sql::ResultSet*			mResult; // result of query
};

