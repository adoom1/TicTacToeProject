#ifndef TEST_GAME_H
#define TEST_GAME_H

#include <QtTest>
#include <QObject>
#include "../Game.h"

class TestGame : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    // Basic game functionality tests
    void testInitialState();
    void testMakeMove();
    void testInvalidMoves();
    void testSwitchPlayer();
    void testCheckWin_data();
    void testCheckWin();
    void testCheckDraw();
    void testGetBoardValue();
    void testGetBoardStateAsString();

    // AI difficulty tests
    void testSetAIDifficulty();
    void testAIMovesEasy();
    void testAIMovesHard();
    void testAIMovesPerfect();

    // Game tree tests
    void testEvaluateBoard();
    void testBuildGameTree();
    void testMinimaxTree();

private:
    Game* game;
};

#endif // TEST_GAME_H
