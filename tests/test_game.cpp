#include "test_game.h"
#include <QSignalSpy>

void TestGame::initTestCase()
{
    // Setup before all tests
}

void TestGame::cleanupTestCase()
{
    // Cleanup after all tests
}

void TestGame::init()
{
    // Setup before each test
    game = new Game();
}

void TestGame::cleanup()
{
    // Cleanup after each test
    delete game;
    game = nullptr;
}

void TestGame::testInitialState()
{
    QCOMPARE(game->getCurrentPlayer(), 'X');

    // Check all board positions are empty
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            QCOMPARE(game->getBoardValue(i, j), ' ');
        }
    }

    QVERIFY(!game->checkWin());
    QVERIFY(!game->checkDraw());
}

void TestGame::testMakeMove()
{
    QVERIFY(game->makeMove(0, 0));
    QCOMPARE(game->getBoardValue(0, 0), 'X');

    game->switchPlayer();
    QVERIFY(game->makeMove(1, 1));
    QCOMPARE(game->getBoardValue(1, 1), 'O');
}

void TestGame::testInvalidMoves()
{
    // Test out of bounds moves
    QVERIFY(!game->makeMove(-1, 0));
    QVERIFY(!game->makeMove(0, -1));
    QVERIFY(!game->makeMove(3, 0));
    QVERIFY(!game->makeMove(0, 3));

    // Test move on occupied position
    game->makeMove(0, 0);
    QVERIFY(!game->makeMove(0, 0));
}

void TestGame::testSwitchPlayer()
{
    QCOMPARE(game->getCurrentPlayer(), 'X');
    game->switchPlayer();
    QCOMPARE(game->getCurrentPlayer(), 'O');
    game->switchPlayer();
    QCOMPARE(game->getCurrentPlayer(), 'X');
}

void TestGame::testCheckWin_data()
{
    QTest::addColumn<QStringList>("moves");
    QTest::addColumn<bool>("shouldWin");
    QTest::addColumn<char>("winner");

    // Horizontal wins
    QTest::newRow("horizontal_top") << (QStringList() << "0,0" << "1,0" << "0,1" << "1,1" << "0,2") << true << 'X';
    QTest::newRow("horizontal_middle") << (QStringList() << "1,0" << "0,0" << "1,1" << "0,1" << "1,2") << true << 'X';
    QTest::newRow("horizontal_bottom") << (QStringList() << "2,0" << "0,0" << "2,1" << "0,1" << "2,2") << true << 'X';

    // Vertical wins
    QTest::newRow("vertical_left") << (QStringList() << "0,0" << "0,1" << "1,0" << "1,1" << "2,0") << true << 'X';
    QTest::newRow("vertical_middle") << (QStringList() << "0,1" << "0,0" << "1,1" << "1,0" << "2,1") << true << 'X';
    QTest::newRow("vertical_right") << (QStringList() << "0,2" << "0,0" << "1,2" << "1,0" << "2,2") << true << 'X';

    // Diagonal wins
    QTest::newRow("diagonal_main") << (QStringList() << "0,0" << "0,1" << "1,1" << "0,2" << "2,2") << true << 'X';
    QTest::newRow("diagonal_anti") << (QStringList() << "0,2" << "0,0" << "1,1" << "1,0" << "2,0") << true << 'X';

    // No win
    QTest::newRow("no_win") << (QStringList() << "0,0" << "0,1" << "1,0") << false << ' ';
}

void TestGame::testCheckWin()
{
    QFETCH(QStringList, moves);
    QFETCH(bool, shouldWin);
    QFETCH(char, winner);

    for (const QString& move : moves) {
        QStringList coords = move.split(',');
        int row = coords[0].toInt();
        int col = coords[1].toInt();

        game->makeMove(row, col);

        if (game->checkWin()) {
            QCOMPARE(shouldWin, true);
            QCOMPARE(game->getCurrentPlayer(), winner);
            return;
        }

        game->switchPlayer();
    }

    QCOMPARE(game->checkWin(), shouldWin);
}

void TestGame::testCheckDraw()
{
    // Fill board without winner
    game->makeMove(0, 0); // X
    game->switchPlayer();
    game->makeMove(0, 1); // O
    game->switchPlayer();
    game->makeMove(0, 2); // X
    game->switchPlayer();
    game->makeMove(1, 0); // O
    game->switchPlayer();
    game->makeMove(1, 2); // X
    game->switchPlayer();
    game->makeMove(1, 1); // O
    game->switchPlayer();
    game->makeMove(2, 0); // X
    game->switchPlayer();
    game->makeMove(2, 2); // O
    game->switchPlayer();
    game->makeMove(2, 1); // X

    QVERIFY(game->checkDraw());
    QVERIFY(!game->checkWin());
}

void TestGame::testGetBoardValue()
{
    game->makeMove(1, 1);
    QCOMPARE(game->getBoardValue(1, 1), 'X');
    QCOMPARE(game->getBoardValue(0, 0), ' ');

    // Test out of bounds
    QCOMPARE(game->getBoardValue(-1, 0), ' ');
    QCOMPARE(game->getBoardValue(3, 0), ' ');
}

void TestGame::testGetBoardStateAsString()
{
    QString expected = "         "; // 9 spaces
    QCOMPARE(QString::fromStdString(game->getBoardStateAsString()), expected);

    game->makeMove(0, 0);
    game->switchPlayer();
    game->makeMove(1, 1);

    QString result = QString::fromStdString(game->getBoardStateAsString());
    QCOMPARE(result[0], 'X');
    QCOMPARE(result[4], 'O');
}

void TestGame::testSetAIDifficulty()
{
    game->setAIDifficulty(AIDifficulty::EASY);
    QCOMPARE(game->getAIDifficulty(), AIDifficulty::EASY);

    game->setAIDifficulty(AIDifficulty::IMPOSSIBLE);
    QCOMPARE(game->getAIDifficulty(), AIDifficulty::IMPOSSIBLE);
}

void TestGame::testAIMovesEasy()
{
    game->setAIDifficulty(AIDifficulty::EASY);

    // AI should make a move (any valid move)
    int emptyCountBefore = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (game->getBoardValue(i, j) == ' ') emptyCountBefore++;
        }
    }

    game->makeAIMove();

    int emptyCountAfter = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (game->getBoardValue(i, j) == ' ') emptyCountAfter++;
        }
    }

    QCOMPARE(emptyCountAfter, emptyCountBefore - 1);
}

void TestGame::testAIMovesHard()
{
    game->setAIDifficulty(AIDifficulty::HARD);

    // Test multiple times to account for randomness
    bool blockedCorrectly = false;

    for (int attempt = 0; attempt < 10; attempt++) {
        // Reset game for each attempt
        delete game;
        game = new Game();
        game->setAIDifficulty(AIDifficulty::HARD);

        // Set up the same scenario
        game->makeMove(0, 0); // X
        game->switchPlayer();
        game->makeMove(0, 1); // O
        game->switchPlayer();
        game->makeMove(1, 0); // X
        game->switchPlayer();

        game->makeAIMove();

        if (game->getBoardValue(2, 0) == 'O') {
            blockedCorrectly = true;
            break;
        }
    }

    // Hard AI should block at least once in 10 attempts
    QVERIFY2(blockedCorrectly, "Hard AI should block winning moves most of the time");
}
void TestGame::testAIMovesPerfect()
{
    game->setAIDifficulty(AIDifficulty::IMPOSSIBLE);

    // Perfect AI should never lose
    // Test that it makes optimal moves
    game->makeMove(0, 0); // X takes corner
    game->switchPlayer(); // O's turn

    game->makeAIMove(); // AI should take center or corner

    char aiMove = game->getBoardValue(1, 1);
    bool tookCenter = (aiMove == 'O');
    bool tookCorner = (game->getBoardValue(0, 2) == 'O' ||
                       game->getBoardValue(2, 0) == 'O' ||
                       game->getBoardValue(2, 2) == 'O');

    QVERIFY(tookCenter || tookCorner);
}

void TestGame::testEvaluateBoard()
{
    char board[3][3] = {
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}
    };

    QCOMPARE(game->evaluateBoard(board), -1); // X wins

    char board2[3][3] = {
        {'O', 'O', 'O'},
        {' ', 'X', ' '},
        {' ', ' ', 'X'}
    };

    QCOMPARE(game->evaluateBoard(board2), 1); // O wins

    char board3[3][3] = {
        {'X', 'O', 'X'},
        {'O', 'X', 'O'},
        {'O', 'X', 'O'}
    };

    QCOMPARE(game->evaluateBoard(board3), 0); // Draw or in progress
}

void TestGame::testBuildGameTree()
{
    char board[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    TreeNode* root = game->buildGameTree(board, 'X');

    QVERIFY(root != nullptr);
    QCOMPARE(root->player, 'X');
    QCOMPARE(root->children.size(), 9); // 9 possible first moves

    // Clean up
    game->deleteTree(root);
}

void TestGame::testMinimaxTree()
{
    // Test with a simple end-game scenario
    char board[3][3] = {
        {'X', 'O', 'X'},
        {'O', 'X', 'O'},
        {'O', ' ', ' '}
    };

    TreeNode* root = game->buildGameTree(board, 'X');
    int score = game->minimaxTree(root, false); // X is minimizing

    QVERIFY(score <= 1 && score >= -1); // Valid minimax score

    // Clean up
    game->deleteTree(root);
}
