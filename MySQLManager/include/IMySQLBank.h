#pragma once
#include <mysql/jdbc.h>

struct IMySQLBankGet
{
	virtual size_t getResultColomns() = 0;

	virtual sql::Driver* getDriverInstance() noexcept = 0;
	virtual sql::Connection* getConnectionInstance() noexcept = 0;
	virtual sql::Statement* getStatementInstance() noexcept = 0;
	virtual sql::PreparedStatement* getPreparedStatementInstance() noexcept = 0;
	virtual sql::ResultSet* getResultInstance() noexcept = 0;
};

struct IMySQLBankUnSafe
{
	virtual uint8_t connect(const std::string& path_to_ticket) = 0;

	virtual bool selectScheme(const std::string& name_db) = 0;

	virtual bool immediatelyExecute(const std::string& query) = 0;
	virtual void prepareExecution(const std::string& query) = 0;
	virtual bool executePrepared() = 0;
	virtual bool executeQuery(const std::string& query) = 0;
	virtual void executeUpdate(const std::string query) = 0;
};

struct IMySQLBankSafe
{
	virtual uint8_t connect(const std::string& path_to_ticket) noexcept = 0;

	virtual bool selectScheme(const std::string& name_db) noexcept = 0;

	virtual bool immediatelyExecute(const std::string& query) noexcept = 0;
	virtual void prepareExecution(const std::string& query) noexcept = 0;
	virtual bool executePrepared() = 0;
	virtual bool executeQuery(const std::string& query) noexcept = 0;
	virtual void executeUpdate(const std::string query) noexcept = 0;
};
