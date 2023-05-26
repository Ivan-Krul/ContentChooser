#pragma once
#include "IMySQLBank.h"

#define ERR_CONNECTION 1
#define ERR_NO_KEY 2

class MySQLBankBase
{
public:
	virtual ~MySQLBankBase();

	sql::Driver* mDriver; // sql drivers for further connection
	sql::Connection* mConnection; // connection statement itself
	sql::Statement* mStatement; // instance statement of db (execute management of databases or table configurations)
	sql::PreparedStatement* mPreparedStatement; // prepared statement of db (execute queries)
	sql::ResultSet* mResult; // result of query
};


class MySQLBankOperatorafe : public MySQLBankBase, public IMySQLBankSafe
{
public:

};


class MySQLBankUnSafe : private MySQLBankBase, public IMySQLBankGet, public IMySQLBankUnSafe
{
public:
	uint8_t connect(const std::string& path_to_ticket) override;

	bool selectScheme(const std::string& name_db) override;

	bool immediatelyExecute(const std::string& query) override;
	void prepareExecution(const std::string& query) override;
	bool executePrepared() override;
	bool executeQuery(const std::string& query) override;
	void executeUpdate(const std::string query) override;

	size_t getResultColomns() override;

	inline sql::Driver* getDriverInstance() noexcept override { return mDriver; };
	inline sql::Connection* getConnectionInstance() noexcept override { return mConnection; };
	inline sql::Statement* getStatementInstance() noexcept override { return mStatement; };
	inline sql::PreparedStatement* getPreparedStatementInstance() noexcept override { return mPreparedStatement; };
	inline sql::ResultSet* getResultInstance() noexcept override { return mResult; };
};


class MySQLBankSafe : private MySQLBankBase, public IMySQLBankGet, public IMySQLBankSafe
{
public:
	uint8_t connect(const std::string& path_to_ticket) noexcept override;

	bool selectScheme(const std::string& name_db) noexcept override;

	bool immediatelyExecute(const std::string& query) noexcept override;
	void prepareExecution(const std::string& query) noexcept override;
	bool executePrepared() override;
	bool executeQuery(const std::string& query) noexcept override;
	void executeUpdate(const std::string query) noexcept override;

	size_t getResultColomns() noexcept override;

	inline sql::Driver* getDriverInstance() noexcept override { return mDriver; };
	inline sql::Connection* getConnectionInstance() noexcept override { return mConnection; };
	inline sql::Statement* getStatementInstance() noexcept override { return mStatement; };
	inline sql::PreparedStatement* getPreparedStatementInstance() noexcept override { return mPreparedStatement; };
	inline sql::ResultSet* getResultInstance() noexcept override { return mResult; };

	virtual ~MySQLBankSafe() = default;
};
