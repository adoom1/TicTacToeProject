#include "test_dbmanager.h"
#include <QFile>

void TestDBManager::initTestCase()
{
    // Remove test database
    QFile::remove("test_tictactoe.db");
}

void TestDBManager::cleanupTestCase()
{
    QFile::remove("test_tictactoe.db");
}

void TestDBManager::init()
{
    db = &DBManager::getInstance();
}

void TestDBManager::cleanup()
{
    // DBManager is singleton, no cleanup needed
}

void TestDBManager::testSingleton()
{
    DBManager& db1 = DBManager::getInstance();
    DBManager& db2 = DBManager::getInstance();

    QCOMPARE(&db1, &db2); // Should be same instance
}

void TestDBManager::testAddUser()
{
    QVERIFY(db->addUser("testuser1", "hashedpass1"));
    QVERIFY(!db->addUser("testuser1", "hashedpass2")); // Duplicate should fail
}

void TestDBManager::testCheckUserCredentials()
{
    db->addUser("credtest", "hashedcreds");

    QVERIFY(db->checkUserCredentials("credtest", "hashedcreds"));
    QVERIFY(!db->checkUserCredentials("credtest", "wronghash"));
    QVERIFY(!db->checkUserCredentials("nonexistent", "anyhash"));
}

void TestDBManager::testUsernameExists()
{
    db->addUser("existstest", "somepass");

    QVERIFY(db->usernameExists("existstest"));
    QVERIFY(!db->usernameExists("doesnotexist"));
}

void TestDBManager::testSaveGameRecord()
{
    GameRecord record("testplayer", "Win", "AI");
    record.boardState = "XOXOXOXOX";

    QVERIFY(db->saveGameRecord(record));
}

void TestDBManager::testGetGameRecords()
{
    // Add a user first
    db->addUser("historytest", "pass");

    // Add some game records
    GameRecord record1("historytest", "Win", "AI");
    record1.boardState = "XOXOXOXOX";
    db->saveGameRecord(record1);

    GameRecord record2("historytest", "Loss", "Human");
    record2.boardState = "OXOXOXOXO";
    db->saveGameRecord(record2);

    std::vector<GameRecord> records = db->getGameRecords("historytest");

    QCOMPARE(records.size(), 2);
    QCOMPARE(records[0].username, std::string("historytest"));
    QCOMPARE(records[1].username, std::string("historytest"));
}
