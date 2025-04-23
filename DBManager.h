#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <string>
#include <vector>
#include <sqlite3.h>
#include "Game.h"

class DBManager {
private:
    DBManager();
    sqlite3* db;
    bool initialized;

    bool initializeDB();
    static int callbackGetRecords(void* data, int argc, char** argv, char** azColName);

public:
    static DBManager& getInstance();
    ~DBManager();

    bool saveGameRecord(const GameRecord& record);
    std::vector<GameRecord> getGameRecords(const std::string& username);

    // User management
    bool addUser(const std::string& username, const std::string& hashedPassword);
    bool checkUserCredentials(const std::string& username, const std::string& hashedPassword);
    bool usernameExists(const std::string& username);
};

#endif // DBMANAGER_H
