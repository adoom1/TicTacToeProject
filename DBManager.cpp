#include "DBManager.h"
#include <iostream>
#include <ctime>
#include <sstream>

DBManager::DBManager() : db(nullptr), initialized(false) {
    initialized = initializeDB();
}

DBManager& DBManager::getInstance() {
    static DBManager instance;
    return instance;
}

DBManager::~DBManager() {
    if (db) {
        sqlite3_close(db);
    }
}

bool DBManager::initializeDB() {
    int rc = sqlite3_open("tictactoe.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    // Create users table
    const char* createUserTableSQL =
        "CREATE TABLE IF NOT EXISTS users ("
        "username TEXT PRIMARY KEY,"
        "password TEXT NOT NULL,"
        "created_at DATETIME DEFAULT CURRENT_TIMESTAMP"
        ");";

    char* errMsg = nullptr;
    rc = sqlite3_exec(db, createUserTableSQL, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }

    // Create game_history table
    const char* createHistoryTableSQL =
        "CREATE TABLE IF NOT EXISTS game_history ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT NOT NULL,"
        "result TEXT NOT NULL,"
        "opponent TEXT NOT NULL,"
        "date TEXT NOT NULL,"
        "board_state TEXT NOT NULL,"
        "FOREIGN KEY (username) REFERENCES users(username)"
        ");";

    rc = sqlite3_exec(db, createHistoryTableSQL, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }

    return true;
}

bool DBManager::addUser(const std::string& username, const std::string& hashedPassword) {
    if (usernameExists(username)) {
        return false;
    }

    sqlite3_stmt* stmt;
    const char* sql = "INSERT INTO users (username, password) VALUES (?, ?);";

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL prepare error: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, hashedPassword.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return rc == SQLITE_DONE;
}

bool DBManager::checkUserCredentials(const std::string& username, const std::string& hashedPassword) {
    sqlite3_stmt* stmt;
    const char* sql = "SELECT COUNT(*) FROM users WHERE username = ? AND password = ?;";

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL prepare error: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, hashedPassword.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    int count = 0;
    if (rc == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    return count > 0;
}

bool DBManager::usernameExists(const std::string& username) {
    sqlite3_stmt* stmt;
    const char* sql = "SELECT COUNT(*) FROM users WHERE username = ?;";

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL prepare error: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    int count = 0;
    if (rc == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    return count > 0;
}

bool DBManager::saveGameRecord(const GameRecord& record) {
    sqlite3_stmt* stmt;
    const char* sql = "INSERT INTO game_history (username, result, opponent, date, board_state) VALUES (?, ?, ?, ?, ?);";

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL prepare error: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, record.username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, record.result.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, record.opponent.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, record.date.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, record.boardState.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return rc == SQLITE_DONE;
}

int DBManager::callbackGetRecords(void* data, int /*argc*/, char** argv, char** /*azColName*/) {
    std::vector<GameRecord>* records = static_cast<std::vector<GameRecord>*>(data);

    // Create a game record from the database row
    GameRecord record(
        argv[0] ? argv[0] : "", // username
        argv[1] ? argv[1] : "", // result
        argv[2] ? argv[2] : ""  // opponent
        );

    record.date = argv[3] ? argv[3] : "";
    record.boardState = argv[4] ? argv[4] : "";

    records->push_back(record);
    return 0;
}

std::vector<GameRecord> DBManager::getGameRecords(const std::string& username) {
    std::vector<GameRecord> records;

    sqlite3_stmt* stmt;
    const char* sql = "SELECT username, result, opponent, date, board_state FROM game_history WHERE username = ? ORDER BY id DESC;";

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL prepare error: " << sqlite3_errmsg(db) << std::endl;
        return records;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        // Create GameRecord from row data
        GameRecord record(
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)), // username
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)), // result
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2))  // opponent
            );

        record.date = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        record.boardState = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));

        records.push_back(record);
    }

    sqlite3_finalize(stmt);
    return records;
}
