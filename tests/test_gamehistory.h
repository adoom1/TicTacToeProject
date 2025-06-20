#ifndef TEST_GAMEHISTORYMODEL_H
#define TEST_GAMEHISTORYMODEL_H

#include <QtTest>
#include <QObject>
#include "../GameHistoryModel.h"
#include "../DBManager.h"

class TestGameHistoryModel : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    void testInitialState();
    void testLoadHistory();
    void testAddGameRecord();
    void testModelData();

private:
    GameHistoryModel* model;
};

#endif // TEST_GAMEHISTORYMODEL_H
