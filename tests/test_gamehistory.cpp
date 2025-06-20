#include "test_gamehistory.h"
#include <QSignalSpy>

void TestGameHistoryModel::initTestCase()
{
    // Setup
}

void TestGameHistoryModel::cleanupTestCase()
{
    // Cleanup
}

void TestGameHistoryModel::init()
{
    model = new GameHistoryModel();
}

void TestGameHistoryModel::cleanup()
{
    delete model;
    model = nullptr;
}

void TestGameHistoryModel::testInitialState()
{
    QCOMPARE(model->rowCount(), 0);
    QCOMPARE(model->columnCount(), 4); // Date, Result, Opponent, Board State
}

void TestGameHistoryModel::testLoadHistory()
{
    // Add a test user and game record first
    DBManager::getInstance().addUser("modeltest", "pass");
    model->addGameRecord("modeltest", "Win", "AI");

    QSignalSpy spy(model, &QAbstractItemModel::modelReset);
    model->loadHistory("modeltest");

    QCOMPARE(spy.count(), 1);
    QVERIFY(model->rowCount() > 0);
}

void TestGameHistoryModel::testAddGameRecord()
{
    DBManager::getInstance().addUser("addtest", "pass");

    QSignalSpy spy(model, &QAbstractItemModel::modelReset);
    model->addGameRecord("addtest", "Win", "AI");

    QVERIFY(spy.count() > 0); // Should trigger model reset
}

void TestGameHistoryModel::testModelData()
{
    DBManager::getInstance().addUser("datatest", "pass");
    model->addGameRecord("datatest", "Win", "AI");
    model->loadHistory("datatest");

    if (model->rowCount() > 0) {
        QModelIndex index = model->index(0, 1); // Result column
        QVariant data = model->data(index, Qt::DisplayRole);
        QCOMPARE(data.toString(), QString("Win"));

        QModelIndex opponentIndex = model->index(0, 2); // Opponent column
        QVariant opponentData = model->data(opponentIndex, Qt::DisplayRole);
        QCOMPARE(opponentData.toString(), QString("AI"));
    }
}
