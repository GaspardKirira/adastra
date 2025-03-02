#include "Adastra/Database.hpp"

namespace Adastra
{
    DatabaseException::DatabaseException(const std::string &message) : message(message) {}

    const char *DatabaseException::what() const noexcept
    {
        return message.c_str();
    }

    std::unique_ptr<Database> Database::instance = nullptr;
    std::mutex Database::mtx;

    Database::Database()
    {
        connect();
    }

    void Database::connect()
    {
        try
        {
            if (!connection)
            {
                sql::mysql::MySQL_Driver *driver = sql::mysql::get_mysql_driver_instance();
                connection = std::shared_ptr<sql::Connection>(driver->connect("tcp://127.0.0.1:3306", "root", ""));
                connection->setSchema("softadastra");
                std::cout << "Connexion à la base de données réussie !" << std::endl;
            }
        }
        catch (sql::SQLException &e)
        {
            throw DatabaseException("Erreur de connexion à la base de données : " + std::string(e.what()));
        }
    }

    std::unique_ptr<sql::ResultSet> Database::executeQuery(const std::string &query)
    {
        try
        {
            std::unique_ptr<sql::Statement> stmt(connection->createStatement());
            return std::unique_ptr<sql::ResultSet>(stmt->executeQuery(query));
        }
        catch (sql::SQLException &e)
        {
            throw DatabaseException("Erreur d'exécution de la requête : " + std::string(e.what()));
        }
    }

    std::unique_ptr<sql::ResultSet> Database::executePreparedQuery(const std::string &query, int param)
    {
        try
        {
            std::unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement(query));
            pstmt->setInt(1, param);
            return std::unique_ptr<sql::ResultSet>(pstmt->executeQuery());
        }
        catch (sql::SQLException &e)
        {
            throw DatabaseException("Erreur d'exécution de la requête préparée : " + std::string(e.what()));
        }
    }

    // Retourne la connexion à la base de données
    std::shared_ptr<sql::Connection> Database::getConnection()
    {
        return connection;
    }

    // Destructeur
    Database::~Database()
    {
        std::cout << "Connexion à la base de données fermée." << std::endl;
    }

    // Fonction pour obtenir l'instance unique de Database
    std::unique_ptr<Database> &Database::getInstance()
    {
        if (!instance)
        {
            std::lock_guard<std::mutex> lock(mtx);
            if (!instance)
            {
                instance = std::make_unique<Database>();
            }
        }
        return instance;
    }

} // namespace Adastra
