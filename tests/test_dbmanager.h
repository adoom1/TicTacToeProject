#ifndef TEST_DBMANAGER_H
#define TEST_DBMANAGER_H

#include <QtTest>
#include <QObject>
#include "../DBManager.h"
#include "../Game.h"


class TestDBManager : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    void testSingleton();
    void testAddUser();
    void testCheckUserCredentials();
    void testUsernameExists();
    void testSaveGameRecord();
    void testGetGameRecords();

private:
    DBManager* db;
};

#endif // TEST_DBMANAGER_H
