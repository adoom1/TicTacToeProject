#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <chrono>

// Define AI difficulty levels
enum class AIDifficulty {
    EASY,
    MEDIUM,
    HARD,
    IMPOSSIBLE
};

struct TreeNode {
    char board[3][3];
    char player; // 'X' or 'O'
    std::vector<TreeNode*> children;
    int score;

    TreeNode(char b[3][3], char p) {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                board[i][j] = b[i][j];
        player = p;
        score = 0;
    }
};

struct GameRecord {
    std::string username;
    std::string result;
    std::string opponent; // "AI" or "Human"
    std::string date;
    std::string boardState;

    GameRecord(const std::string& u, const std::string& r, const std::string& o)
        : username(u), result(r), opponent(o) {
        auto now = std::chrono::system_clock::now();
        auto now_time = std::chrono::system_clock::to_time_t(now);
        date = std::ctime(&now_time);
    }
};

class Game {
private:
    std::vector<std::vector<char>> board;
    char currentPlayer; // Now always 'X' initially for a new game logic start
    int minimax(int depth, bool isMaximizing); // Existing, but not currently used for AI logic (minimaxTree is)
    std::vector<GameRecord> gameHistory;
    AIDifficulty aiDifficulty;
    void makeEasyAIMove();
    void makeMediumAIMove();
    void makeHardAIMove(); // Updated logic
    bool findImminentWinOrBlock();
    void deleteTree(TreeNode* node);

public:
    Game(); // Constructor initializes currentPlayer to 'X'
    void displayBoard();
    bool makeMove(int row, int col);
    bool checkWin();
    bool checkDraw();
    void switchPlayer();
    char getCurrentPlayer();
    char getBoardValue(int row, int col);
    std::string getBoardStateAsString();

    // Set/get AI difficulty
    void setAIDifficulty(AIDifficulty difficulty);
    AIDifficulty getAIDifficulty() const;

    // Game Tree AI functions
    TreeNode* buildGameTree(char b[3][3], char currentPlayer);
    int evaluateBoard(char b[3][3]);
    int minimaxTree(TreeNode* node, bool isMaximizing); // Used by IMPOSSIBLE
    void makeAIMoveWithTree(); // Used by IMPOSSIBLE
    void makeAIMoveWithLimitedTree(int depthLimit); // NEW: Used by HARD
    void makeAIMove(); // New function to handle difficulty levels

    // Game history functions
    void saveGame(const std::string& username, const std::string& result, const std::string& opponent);
    std::vector<GameRecord> getGameHistory(const std::string& username);

    // Removed setStartingPlayer as Game will always start with 'X' internally.
    // The MainWindow logic will manage who moves first based on human's chosen mark.
};

#endif // GAME_H
