#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <chrono>

using namespace std; // Added: using namespace std

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
    vector<TreeNode*> children;
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
    string username;
    string result;
    string opponent; // "AI" or "Human"
    string date;
    string boardState;

    GameRecord(const string& u, const string& r, const string& o)
        : username(u), result(r), opponent(o) {
        auto now = chrono::system_clock::now();
        auto now_time = chrono::system_clock::to_time_t(now);
        date = ctime(&now_time);
    }
};

class Game {
private:
    vector<vector<char>> board;
    char currentPlayer; // Now always 'X' initially for a new game logic start
    int minimax(int depth, bool isMaximizing); // Existing, but not currently used for AI logic (minimaxTree is)
    vector<GameRecord> gameHistory;
    AIDifficulty aiDifficulty;
    void makeEasyAIMove();
    void makeMediumAIMove();
    void makeHardAIMove(); // Updated logic
    bool findImminentWinOrBlock();


public:
    Game(); // Constructor initializes currentPlayer to 'X'
    void displayBoard();
    bool makeMove(int row, int col);
    bool checkWin();
    bool checkDraw();
    void switchPlayer();
    char getCurrentPlayer();
    char getBoardValue(int row, int col);
    string getBoardStateAsString();
 void deleteTree(TreeNode* node);

    // Set/get AI difficulty
    void setAIDifficulty(AIDifficulty difficulty);
    AIDifficulty getAIDifficulty() const;

    // Game Tree AI functions
    TreeNode* buildGameTree(char b[3][3], char currentPlayer);
    int evaluateBoard(char b[3][3]);
    // Changed minimaxTree signature to include alpha and beta
    int minimaxTree(TreeNode* node, int alpha, int beta, bool isMaximizing); // Used by IMPOSSIBLE
    void makeAIMoveWithTree(); // Used by IMPOSSIBLE
    void makeAIMoveWithLimitedTree(int depthLimit); // NEW: Used by HARD
    void makeAIMove(); // New function to handle difficulty levels

    // Game history functions
    void saveGame(const string& username, const string& result, const string& opponent);
    vector<GameRecord> getGameHistory(const string& username);

    // Removed setStartingPlayer as Game will always start with 'X' internally.
    // The MainWindow logic will manage who moves first based on human's chosen mark.
};

#endif // GAME_H
