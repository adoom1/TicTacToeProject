#include <QtTest>
#include <QApplication>
#include "test_performance.h"

#include "test_game.h"
#include "test_gamehistory.h"
#include "test_dbmanager.h"
#include "test_user.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    int status = 0;

    // Run Performance test
    {
        qDebug() << "\n--- Running Performance Tests ---";
        TestPerformance performanceTest;
        status |= QTest::qExec(&performanceTest, argc, argv);
    }
    //Run game test
      //{
    //TestGame gameTest;
    //status |= QTest::qExec(&gameTest, argc, argv);
    //}
    // Run User tests


    //{
       // TestUser userTest;
        //status |= QTest::qExec(&userTest, argc, argv);
    //}


    // Run DBManager tests
    //{
        //TestDBManager dbTest;
       // status |= QTest::qExec(&dbTest, argc, argv);
    //}

    // Run GameHistoryModel tests
    //{
       // TestGameHistoryModel modelTest;
        //status |= QTest::qExec(&modelTest, argc, argv);
    //}


    return status;


}
