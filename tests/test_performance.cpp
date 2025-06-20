#include "test_performance.h"
#include <QDebug>
#include <QCoreApplication>
#include <random>
#include <algorithm>

void TestPerformance::initTestCase()
{
    qDebug() << "=== Starting Performance Test Suite ===";
    qDebug() << "System Information:";
    qDebug() << "- Qt Version:" << QT_VERSION_STR;
    qDebug() << "- Thread Count:" << QThread::idealThreadCount();
    qDebug() << "- Application PID:" << QCoreApplication::applicationPid();
}

void TestPerformance::cleanupTestCase()
{
    qDebug() << "=== Performance Test Suite Completed ===";
}

void TestPerformance::init()
{
    game = new Game();
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void TestPerformance::cleanup()
{
    delete game;
    game = nullptr;
}

void TestPerformance::benchmarkAIMoveEasy()
{
    game->setAIDifficulty(AIDifficulty::EASY);
    
    QBENCHMARK {
        // Reset game for each iteration
        delete game;
        game = new Game();
        game->setAIDifficulty(AIDifficulty::EASY);
        
        // Create a realistic mid-game scenario
        game->makeMove(0, 0); // X
        game->switchPlayer();
        
        // Benchmark the AI move
        game->makeAIMove();
    }
    
    qDebug() << "Easy AI Move benchmark completed";
}

void TestPerformance::benchmarkAIMoveMedium()
{
    game->setAIDifficulty(AIDifficulty::MEDIUM);
    
    QBENCHMARK {
        delete game;
        game = new Game();
        game->setAIDifficulty(AIDifficulty::MEDIUM);
        
        // Create more complex scenario
        game->makeMove(0, 0); // X
        game->switchPlayer();
        game->makeMove(1, 1); // O
        game->switchPlayer();
        
        game->makeAIMove();
    }
    
    qDebug() << "Medium AI Move benchmark completed";
}

void TestPerformance::benchmarkAIMoveHard()
{
    game->setAIDifficulty(AIDifficulty::HARD);
    
    QBENCHMARK {
        delete game;
        game = new Game();
        game->setAIDifficulty(AIDifficulty::HARD);
        
        // Create strategic scenario requiring analysis
        game->makeMove(0, 0); // X
        game->switchPlayer();
        game->makeMove(0, 1); // O
        game->switchPlayer();
        game->makeMove(1, 0); // X
        game->switchPlayer();
        
        game->makeAIMove();
    }
    
    qDebug() << "Hard AI Move benchmark completed";
}

void TestPerformance::benchmarkAIMoveImpossible()
{
    game->setAIDifficulty(AIDifficulty::IMPOSSIBLE);
    
    QBENCHMARK {
        delete game;
        game = new Game();
        game->setAIDifficulty(AIDifficulty::IMPOSSIBLE);
        
        // Create complex board state for minimax
        game->makeMove(0, 0); // X
        game->switchPlayer();
        game->makeMove(1, 1); // O
        game->switchPlayer();
        game->makeMove(0, 2); // X
        game->switchPlayer();
        
        game->makeAIMove(); // Uses minimax tree
    }
    
    qDebug() << "Impossible AI Move benchmark completed";
}

void TestPerformance::benchmarkGameTreeBuilding()
{
    char testBoard[3][3] = {
        {'X', ' ', 'O'},
        {' ', 'X', ' '},
        {'O', ' ', ' '}
    };
    
    QBENCHMARK {
        TreeNode* root = game->buildGameTree(testBoard, 'X');
        game->deleteTree(root);
    }
    
    qDebug() << "Game Tree Building benchmark completed";
}

void TestPerformance::benchmarkMinimaxCalculation()
{
    char testBoard[3][3] = {
        {'X', ' ', ' '},
        {' ', 'O', ' '},
        {' ', ' ', ' '}
    };
    
    QBENCHMARK {
        TreeNode* root = game->buildGameTree(testBoard, 'X');
int alpha = -1000;
        int beta = 1000;
        game->minimaxTree(root,alpha,beta,false);
        game->deleteTree(root);
    }
    
    qDebug() << "Minimax Calculation benchmark completed";
}

void TestPerformance::benchmarkBoardEvaluation()
{
    char testBoard[3][3] = {
        {'X', 'O', 'X'},
        {'O', 'X', 'O'},
        {'O', ' ', ' '}
    };
    
    QBENCHMARK {
        game->evaluateBoard(testBoard);
    }
    
    qDebug() << "Board Evaluation benchmark completed";
}

void TestPerformance::benchmarkBoardEvaluationBatch()
{
    // Create multiple board states for batch testing
    char testBoards[10][3][3] = {
        {{'X', 'X', 'X'}, {' ', 'O', ' '}, {' ', ' ', 'O'}}, // X wins
        {{'O', 'O', 'O'}, {' ', 'X', ' '}, {' ', ' ', 'X'}}, // O wins
        {{'X', 'O', 'X'}, {'O', 'X', 'O'}, {'O', 'X', 'O'}}, // Draw
        {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}}, // Empty
        {{'X', 'O', ' '}, {'O', 'X', ' '}, {' ', ' ', ' '}}, // In progress
        {{'X', ' ', 'O'}, {' ', 'X', ' '}, {'O', ' ', 'X'}}, // Diagonal win
        {{'X', 'X', 'O'}, {'O', 'O', 'X'}, {'X', 'O', 'X'}}, // Complex
        {{'O', 'X', 'X'}, {'X', 'O', 'O'}, {'O', 'X', 'O'}}, // Complex 2
        {{'X', 'O', 'X'}, {'X', 'O', 'O'}, {'O', 'X', 'X'}}, // Complex 3
        {{'O', 'X', 'O'}, {'X', 'X', 'O'}, {'X', 'O', 'X'}}  // Complex 4
    };
    
    QBENCHMARK {
        for (int i = 0; i < 10; i++) {
            game->evaluateBoard(testBoards[i]);
        }
    }
    
    qDebug() << "Batch Board Evaluation benchmark completed";
}

void TestPerformance::benchmarkFullGameSimulation()
{
    QBENCHMARK {
        simulateCompleteGame();
    }
    
    qDebug() << "Full Game Simulation benchmark completed";
}

void TestPerformance::benchmarkMultipleGameSimulations()
{
    QBENCHMARK {
        for (int i = 0; i < 10; i++) {
            simulateCompleteGame();
        }
    }
    
    qDebug() << "Multiple Game Simulations benchmark completed";
}

void TestPerformance::benchmarkMemoryUsage()
{
    long long initialMemory = getCurrentMemoryUsage();
    
    QBENCHMARK {
        // Create multiple game instances to test memory allocation
        std::vector<Game*> games = createGamePool(50);
        
        // Perform operations on each game
        for (Game* g : games) {
            g->setAIDifficulty(AIDifficulty::IMPOSSIBLE);
            g->makeMove(0, 0);
            g->switchPlayer();
            g->makeAIMove();
        }
        
        // Clean up
        cleanupGamePool(games);
    }
    
    long long finalMemory = getCurrentMemoryUsage();
    qDebug() << "Memory usage test - Initial:" << initialMemory << "KB, Final:" << finalMemory << "KB";
}

void TestPerformance::benchmarkMemoryLeakTest()
{
    long long initialMemory = getCurrentMemoryUsage();
    
    // Perform memory-intensive operations
    for (int iteration = 0; iteration < 100; iteration++) {
        std::vector<Game*> games = createGamePool(20);
        
        for (Game* g : games) {
            g->setAIDifficulty(AIDifficulty::IMPOSSIBLE);
            char board[3][3] = {{'X', ' ', ' '}, {' ', 'O', ' '}, {' ', ' ', ' '}};
            TreeNode* root = g->buildGameTree(board, 'X');
int alpha = -1000;
            int beta = 1000;
            g->minimaxTree(root,alpha,beta,false);
            g->deleteTree(root);
        }
        
        cleanupGamePool(games);
        
        if (iteration % 20 == 0) {
            long long currentMemory = getCurrentMemoryUsage();
            qDebug() << "Memory leak test iteration" << iteration << "- Memory:" << currentMemory << "KB";
        }
    }
    
    long long finalMemory = getCurrentMemoryUsage();
    long long memoryDiff = finalMemory - initialMemory;
    
    qDebug() << "Memory leak test completed";
    qDebug() << "Initial memory:" << initialMemory << "KB";
    qDebug() << "Final memory:" << finalMemory << "KB";
    qDebug() << "Memory difference:" << memoryDiff << "KB";
    
    // Assert that memory usage hasn't grown excessively (allowing for some OS overhead)
    QVERIFY2(memoryDiff < 1000, "Potential memory leak detected - memory usage increased significantly");
}

void TestPerformance::benchmarkConcurrentGames()
{
    const int gameCount = 20;
    
    QBENCHMARK {
        std::vector<Game*> games = createGamePool(gameCount);
        
        // Simulate concurrent game operations
        for (int round = 0; round < 5; round++) {
            for (Game* g : games) {
                if (round % 2 == 0) {
                    g->makeMove(round % 3, (round + 1) % 3);
                } else {
                    g->switchPlayer();
                    g->makeAIMove();
                }
            }
        }
        
        cleanupGamePool(games);
    }
    
    qDebug() << "Concurrent Games benchmark completed";
}

void TestPerformance::performanceStressTest()
{
    QElapsedTimer timer;
    timer.start();
    
    const int iterations = 500;
    AIDifficulty difficulties[] = {AIDifficulty::EASY, AIDifficulty::MEDIUM, 
                                  AIDifficulty::HARD, AIDifficulty::IMPOSSIBLE};
    
    int completedIterations = 0;
    
    for (int i = 0; i < iterations; i++) {
        delete game;
        game = new Game();
        game->setAIDifficulty(difficulties[i % 4]);
        
        // Create random board state
        fillBoardRandomly(40); // Fill 40% of board randomly
        
        // Make AI move
        game->makeAIMove();
        
        completedIterations++;
        
        // Progress indicator every 100 iterations
        if (i % 100 == 0) {
            qDebug() << "Stress test progress:" << i << "/" << iterations;
        }
    }
    
    qint64 elapsedMs = timer.elapsed();
    double avgTimePerMove = (double)elapsedMs / completedIterations;
    
    logPerformanceMetrics("Stress Test", elapsedMs, completedIterations);
    
    qDebug() << "Average time per AI move:" << avgTimePerMove << "ms";
    qDebug() << "Moves per second:" << (1000.0 / avgTimePerMove);
    
    // Performance assertions
    QVERIFY2(avgTimePerMove < 50.0, "AI moves should average less than 50ms");
    QVERIFY2(elapsedMs < 30000, "Stress test should complete within 30 seconds");
}

void TestPerformance::performanceScalabilityTest()
{
    QElapsedTimer timer;
    
    // Test with increasing numbers of simultaneous games
    QList<int> gameCounts = {1, 5, 10, 20, 50, 100};
    
    for (int gameCount : gameCounts) {
        timer.restart();
        
        std::vector<Game*> games = createGamePool(gameCount);
        
        // Perform operations on all games
        for (Game* g : games) {
            g->setAIDifficulty(AIDifficulty::HARD);
            g->makeMove(0, 0);
            g->switchPlayer();
            g->makeAIMove();
        }
        
        qint64 elapsed = timer.elapsed();
        double avgTimePerGame = (double)elapsed / gameCount;
        
        qDebug() << "Scalability test -" << gameCount << "games:" << elapsed << "ms total," 
                 << avgTimePerGame << "ms per game";
        
        cleanupGamePool(games);
        
        // Verify that performance doesn't degrade too much with scale
        QVERIFY2(avgTimePerGame < 100.0, "Performance should scale reasonably with game count");
    }
}

void TestPerformance::performanceCPUIntensiveTest()
{
    QElapsedTimer timer;
    timer.start();
    
    // Perform CPU-intensive operations
    const int treeBuilds = 100;
    
    for (int i = 0; i < treeBuilds; i++) {
        char board[3][3] = {
            {'X', ' ', 'O'},
            {' ', 'X', ' '},
            {'O', ' ', ' '}
        };
        
        TreeNode* root = game->buildGameTree(board, 'X');
int alpha = -1000;
        int beta = 1000;
        game->minimaxTree(root,alpha,beta,false);
        game->deleteTree(root);
        
        if (i % 20 == 0) {
            qDebug() << "CPU intensive test progress:" << i << "/" << treeBuilds;
        }
    }
    
    qint64 elapsed = timer.elapsed();
    double avgTimePerTree = (double)elapsed / treeBuilds;
    
    logPerformanceMetrics("CPU Intensive Test", elapsed, treeBuilds);
    
    qDebug() << "Average time per tree build+minimax:" << avgTimePerTree << "ms";
    
    // CPU performance assertion
    QVERIFY2(avgTimePerTree < 20.0, "Tree operations should complete within reasonable time");
}

void TestPerformance::compareAIDifficultyPerformance()
{
    QElapsedTimer timer;
    const int iterations = 100;
    
    AIDifficulty difficulties[] = {AIDifficulty::EASY, AIDifficulty::MEDIUM, 
                                  AIDifficulty::HARD, AIDifficulty::IMPOSSIBLE};
    QString difficultyNames[] = {"Easy", "Medium", "Hard", "Impossible"};
    
    qDebug() << "=== AI Difficulty Performance Comparison ===";
    
    for (int d = 0; d < 4; d++) {
        timer.restart();
        
        for (int i = 0; i < iterations; i++) {
            delete game;
            game = new Game();
            game->setAIDifficulty(difficulties[d]);
            
            // Create consistent test scenario
            game->makeMove(0, 0);
            game->switchPlayer();
            game->makeMove(1, 1);
            game->switchPlayer();
            
            game->makeAIMove();
        }
        
        qint64 elapsed = timer.elapsed();
        double avgTime = (double)elapsed / iterations;
        
        qDebug() << difficultyNames[d] << "difficulty - Total:" << elapsed << "ms, Average:" 
                 << avgTime << "ms per move";
    }
}

void TestPerformance::compareAlgorithmEfficiency()
{
    QElapsedTimer timer;
    const int iterations = 50;
    
    // Test different board evaluation scenarios
    char scenarios[3][3][3] = {
        {{'X', ' ', ' '}, {' ', 'O', ' '}, {' ', ' ', ' '}}, // Early game
        {{'X', 'O', 'X'}, {'O', 'X', ' '}, {' ', ' ', 'O'}}, // Mid game
        {{'X', 'O', 'X'}, {'O', 'X', 'O'}, {'O', ' ', ' '}}  // Late game
    };
    
    QString scenarioNames[] = {"Early Game", "Mid Game", "Late Game"};
    
    qDebug() << "=== Algorithm Efficiency Comparison ===";
    
    for (int s = 0; s < 3; s++) {
        timer.restart();
        
        for (int i = 0; i < iterations; i++) {
            TreeNode* root = game->buildGameTree(scenarios[s], 'X');
int alpha = -1000;
            int beta = 1000;
            game->minimaxTree(root,alpha,beta,false);
            game->deleteTree(root);
        }
        
        qint64 elapsed = timer.elapsed();
        double avgTime = (double)elapsed / iterations;
        
        qDebug() << scenarioNames[s] << "- Total:" << elapsed << "ms, Average:" 
                 << avgTime << "ms per tree operation";
    }
}

// Helper method implementations
void TestPerformance::fillBoardRandomly(int fillPercentage)
{
    int cellsToFill = (9 * fillPercentage) / 100;
    char players[] = {'X', 'O'};
    
    for (int filled = 0; filled < cellsToFill; filled++) {
        int row, col;
        do {
            row = rand() % 3;
            col = rand() % 3;
        } while (game->getBoardValue(row, col) != ' ');
        
        game->makeMove(row, col);
        game->switchPlayer();
    }
}

void TestPerformance::simulateCompleteGame()
{
    delete game;
    game = new Game();
    game->setAIDifficulty(AIDifficulty::HARD);
    
    int moveCount = 0;
    while (!game->checkWin() && !game->checkDraw() && moveCount < 9) {
        if (game->getCurrentPlayer() == 'X') {
            // Human-like random move
            std::vector<std::pair<int, int>> availableMoves;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (game->getBoardValue(i, j) == ' ') {
                        availableMoves.push_back({i, j});
                    }
                }
            }
            
            if (!availableMoves.empty()) {
                auto move = availableMoves[rand() % availableMoves.size()];
                game->makeMove(move.first, move.second);
            }
        } else {
            // AI move
            game->makeAIMove();
        }
        
        game->switchPlayer();
        moveCount++;
    }
}

void TestPerformance::createComplexBoardState()
{
    // Create a complex mid-game scenario
    game->makeMove(0, 0); // X
    game->switchPlayer();
    game->makeMove(1, 1); // O
    game->switchPlayer();
    game->makeMove(0, 2); // X
    game->switchPlayer();
    game->makeMove(2, 0); // O
    game->switchPlayer();
}

long long TestPerformance::getCurrentMemoryUsage()
{
    // Simplified memory usage estimation
#ifdef Q_OS_WIN
    // Windows implementation would go here
    return 0;
#else
    QProcess process;
    process.start("ps", QStringList() << "-o" << "rss=" << "-p" << QString::number(QCoreApplication::applicationPid()));
    process.waitForFinished();
    QString output = process.readAllStandardOutput().trimmed();
    return output.toLongLong();
#endif
}

double TestPerformance::calculateCPUUsage()
{
    // Placeholder for CPU usage calculation
    // This would require platform-specific implementation
    return 0.0;
}

void TestPerformance::logPerformanceMetrics(const QString& testName, qint64 elapsedMs, int iterations)
{
    qDebug() << "=== Performance Metrics for" << testName << "===";
    qDebug() << "Total iterations:" << iterations;
    qDebug() << "Total time:" << elapsedMs << "ms";
    qDebug() << "Average time per iteration:" << ((double)elapsedMs / iterations) << "ms";
    qDebug() << "Operations per second:" << (1000.0 * iterations / elapsedMs);
}

std::vector<Game*> TestPerformance::createGamePool(int count)
{
    std::vector<Game*> games;
    games.reserve(count);
    
    for (int i = 0; i < count; i++) {
        games.push_back(new Game());
    }
    
    return games;
}

void TestPerformance::cleanupGamePool(std::vector<Game*>& games)
{
    for (Game* g : games) {
        delete g;
    }
    games.clear();
}


