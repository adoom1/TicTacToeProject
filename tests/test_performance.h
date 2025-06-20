#ifndef TEST_PERFORMANCE_H
#define TEST_PERFORMANCE_H

#include <QtTest>
#include <QObject>
#include <QElapsedTimer>
#include <QProcess>
#include <QThread>
#include <chrono>
#include "../Game.h"

class TestPerformance : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();
    
    // CPU Performance Benchmarks
    void benchmarkAIMoveEasy();
    void benchmarkAIMoveMedium();
    void benchmarkAIMoveHard();
    void benchmarkAIMoveImpossible();
    
    // Algorithm Performance Tests
    void benchmarkGameTreeBuilding();
    void benchmarkMinimaxCalculation();
    void benchmarkBoardEvaluation();
    void benchmarkBoardEvaluationBatch();
    
    // Game Simulation Performance
    void benchmarkFullGameSimulation();
    void benchmarkMultipleGameSimulations();
    
    // Memory and Resource Tests
    void benchmarkMemoryUsage();
    void benchmarkMemoryLeakTest();
    void benchmarkConcurrentGames();
    
    // Stress Tests
    void performanceStressTest();
    void performanceScalabilityTest();
    void performanceCPUIntensiveTest();
    
    // Comparative Performance Tests
    void compareAIDifficultyPerformance();
    void compareAlgorithmEfficiency();

private:
    Game* game;
    
    // Helper methods for performance testing
    void fillBoardRandomly(int fillPercentage);
    void simulateCompleteGame();
    void createComplexBoardState();
    long long getCurrentMemoryUsage();
    double calculateCPUUsage();
    void logPerformanceMetrics(const QString& testName, qint64 elapsedMs, int iterations);
    std::vector<Game*> createGamePool(int count);
    void cleanupGamePool(std::vector<Game*>& games);
};

#endif // TEST_PERFORMANCE_H
