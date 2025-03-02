#ifndef ADASTRA_DATABASE_H
#define ADASTRA_DATABASE_H

#include <iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <cppconn/prepared_statement.h>

namespace Adastra
{
    class DatabaseException : public std::exception
    {
    public:
        explicit DatabaseException(const std::string &message);
        const char *what() const noexcept override;

    private:
        std::string message;
    };

    class Database
    {
    private:
        static std::unique_ptr<Database> instance;
        static std::mutex mtx;
        std::shared_ptr<sql::Connection> connection;

    public:
        Database();
        void connect();
        std::unique_ptr<sql::ResultSet> executeQuery(const std::string &query);
        std::unique_ptr<sql::ResultSet> executePreparedQuery(const std::string &query, int param);
        std::shared_ptr<sql::Connection> getConnection();
        ~Database();

        Database(const Database &) = delete;
        Database &operator=(const Database &) = delete;

        static std::unique_ptr<Database> &getInstance();
    };

#endif // DATABASE_H
} // namespace Adastra
