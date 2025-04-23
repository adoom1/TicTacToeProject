#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>
#include "Game.h"
#include "DBManager.h"

Game::Game() {
    board = std::vector<std::vector<char>>(3, std::vector<char>(3, ' '));
    currentPlayer = 'X';
    aiDifficulty = AIDifficulty::MEDIUM; // Default to medium difficulty
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Initialize random seed
}

void Game::setAIDifficulty(AIDifficulty difficulty) {
    aiDifficulty = difficulty;
}

AIDifficulty Game::getAIDifficulty() const {
    return aiDifficulty;
}

void Game::displayBoard() {
    std::cout << "\n";
    for (int i = 0; i < 3; i++) {
        std::cout << " ";
        for (int j = 0; j < 3; j++) {
            std::cout << board[i][j];
            if (j < 2) std::cout << " | ";
        }
        std::cout << "\n";
        if (i < 2) std::cout << "---+---+---\n";
    }
    std::cout << "\n";
}

bool Game::makeMove(int row, int col) {
    if (row < 0 || row > 2 || col < 0 || col > 2) return false;
    if (board[row][col] != ' ') return false;

    board[row][col] = currentPlayer;
    return true;
}

bool Game::checkWin() {
    for (int i = 0; i < 3; i++) {
        // rows and columns
        if ((board[i][0] == currentPlayer &&
             board[i][1] == currentPlayer &&
             board[i][2] == currentPlayer) ||
            (board[0][i] == currentPlayer &&
             board[1][i] == currentPlayer &&
             board[2][i] == currentPlayer))
            return true;
    }
    // diagonals
    if ((board[0][0] == currentPlayer &&
         board[1][1] == currentPlayer &&
         board[2][2] == currentPlayer) ||
        (board[0][2] == currentPlayer &&
         board[1][1] == currentPlayer &&
         board[2][0] == currentPlayer))
        return true;

    return false;
}

bool Game::checkDraw() {
    for (auto& row : board) {
        for (auto& cell : row) {
            if (cell == ' ') return false;
        }
    }
    return !checkWin(); // draw only if there's no winner
}

void Game::switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

char Game::getCurrentPlayer() {
    return currentPlayer;
}

char Game::getBoardValue(int row, int col) {
    if (row >= 0 && row < 3 && col >= 0 && col < 3) {
        return board[row][col];
    }
    return ' ';
}

std::string Game::getBoardStateAsString() {
    std::stringstream ss;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            ss << board[i][j];
        }
    }
    return ss.str();
}

int Game::evaluateBoard(char b[3][3]) {
    // Check rows, columns and diagonals for win
    for (int i = 0; i < 3; ++i) {
        if (b[i][0] == b[i][1] && b[i][1] == b[i][2] && b[i][0] != ' ')
            return (b[i][0] == 'O') ? 1 : -1;
        if (b[0][i] == b[1][i] && b[1][i] == b[2][i] && b[0][i] != ' ')
            return (b[0][i] == 'O') ? 1 : -1;
    }
    if (b[0][0] == b[1][1] && b[1][1] == b[2][2] && b[0][0] != ' ')
        return (b[0][0] == 'O') ? 1 : -1;
    if (b[0][2] == b[1][1] && b[1][1] == b[2][0] && b[0][2] != ' ')
        return (b[0][2] == 'O') ? 1 : -1;
    return 0;
}

bool isDraw(char b[3][3]) {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (b[i][j] == ' ') return false;
    return true;
}

TreeNode* Game::buildGameTree(char b[3][3], char currentPlayer) {
    TreeNode* node = new TreeNode(b, currentPlayer);
    int score = evaluateBoard(b);
    if (score != 0 || isDraw(b)) {
        node->score = score;
        return node;
    }

    char nextPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (b[i][j] == ' ') {
                char newBoard[3][3];
                for (int x = 0; x < 3; ++x)
                    for (int y = 0; y < 3; ++y)
                        newBoard[x][y] = b[x][y];

                newBoard[i][j] = currentPlayer;
                TreeNode* child = buildGameTree(newBoard, nextPlayer);
                node->children.push_back(child);
            }
        }
    }

    return node;
}

int Game::minimaxTree(TreeNode* node, bool isMaximizing) {
    if (node->children.empty()) return node->score;

    int bestScore = isMaximizing ? -1000 : 1000;
    for (TreeNode* child : node->children) {
        int score = minimaxTree(child, !isMaximizing);
        bestScore = isMaximizing ? std::max(score, bestScore) : std::min(score, bestScore);
    }

    node->score = bestScore;
    return bestScore;
}

// New function that handles AI moves with different difficulty levels
void Game::makeAIMove() {
    switch (aiDifficulty) {
    case AIDifficulty::EASY:
        makeEasyAIMove();
        break;
    case AIDifficulty::MEDIUM:
        makeMediumAIMove();
        break;
    case AIDifficulty::HARD:
        makeHardAIMove();
        break;
    case AIDifficulty::IMPOSSIBLE:
        makeAIMoveWithTree(); // Use the existing minimax tree implementation
        break;
    default:
        makeAIMoveWithTree(); // Default to the perfect AI
        break;
    }
}

// Helper function for EASY difficulty - makes random moves
void Game::makeEasyAIMove() {
    std::vector<std::pair<int, int>> availableMoves;

    // Collect all available moves
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ') {
                availableMoves.push_back(std::make_pair(i, j));
            }
        }
    }

    if (!availableMoves.empty()) {
        // Choose a random move
        int randomIndex = rand() % availableMoves.size();
        int row = availableMoves[randomIndex].first;
        int col = availableMoves[randomIndex].second;
        board[row][col] = currentPlayer;
    }
}

// Helper function for MEDIUM difficulty - sometimes makes optimal moves, sometimes random
void Game::makeMediumAIMove() {
    // 60% chance to make a random move, 40% chance to make the best move
    int randomChoice = rand() % 100;

    if (randomChoice < 60) {
        makeEasyAIMove(); // Make a random move
    } else {
        // Try to find a winning move or block opponent's winning move
        if (!findImminentWinOrBlock()) {
            // If no immediate win/block, make a random move
            makeEasyAIMove();
        }
    }
}

// Helper function for HARD difficulty - mostly makes optimal moves but sometimes makes mistakes
void Game::makeHardAIMove() {
    // 20% chance to make a random move, 80% chance to make the best move
    int randomChoice = rand() % 100;

    if (randomChoice < 20) {
        makeEasyAIMove(); // Make a random move
    } else {
        // Check for a winning move or block a player's winning move
        if (!findImminentWinOrBlock()) {
            // Try to take the center if available
            if (board[1][1] == ' ') {
                board[1][1] = currentPlayer;
                return;
            }

            // Try to take a corner if available
            std::vector<std::pair<int, int>> corners = {{0,0}, {0,2}, {2,0}, {2,2}};
            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(corners.begin(), corners.end(), g);

            for (const auto& corner : corners) {
                if (board[corner.first][corner.second] == ' ') {
                    board[corner.first][corner.second] = currentPlayer;
                    return;
                }
            }

            // If no corner available, make a random move
            makeEasyAIMove();
        }
    }
}

// Helper function to find winning move or block opponent's winning move
bool Game::findImminentWinOrBlock() {
    char opponent = (currentPlayer == 'X') ? 'O' : 'X';

    // First check if AI can win in one move
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ') {
                // Try this move
                board[i][j] = currentPlayer;

                // Check if this wins
                bool wins = checkWin();

                // Undo move
                board[i][j] = ' ';

                if (wins) {
                    // Make the winning move
                    board[i][j] = currentPlayer;
                    return true;
                }
            }
        }
    }

    // Then check if player is about to win and block them
    char savedCurrentPlayer = currentPlayer;
    currentPlayer = opponent;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ') {
                // Try opponent's move
                board[i][j] = opponent;

                // Check if opponent would win
                bool opponentWins = checkWin();

                // Undo move
                board[i][j] = ' ';

                if (opponentWins) {
                    // Block the opponent's winning move
                    board[i][j] = savedCurrentPlayer;
                    currentPlayer = savedCurrentPlayer;
                    return true;
                }
            }
        }
    }

    // Restore current player
    currentPlayer = savedCurrentPlayer;
    return false;
}

void Game::makeAIMoveWithTree() {
    char tempBoard[3][3];
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            tempBoard[i][j] = board[i][j]; // convert vector to array

    TreeNode* root = buildGameTree(tempBoard, 'O');
    minimaxTree(root, true);

    int bestScore = -1000;
    TreeNode* bestMove = nullptr;
    for (TreeNode* child : root->children) {
        if (child->score > bestScore) {
            bestScore = child->score;
            bestMove = child;
        }
    }

    if (bestMove) {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                board[i][j] = bestMove->board[i][j]; // update the actual vector board
    }

    // Clean up the tree to avoid memory leaks
    deleteTree(root); // Add this helper function to clean up the tree
}

// Helper function to delete the tree and free memory
void Game::deleteTree(TreeNode* node) {
    if (!node) return;

    for (TreeNode* child : node->children) {
        deleteTree(child);
    }

    delete node;
}

void Game::saveGame(const std::string& username, const std::string& result, const std::string& opponent) {
    GameRecord record(username, result, opponent);
    record.boardState = getBoardStateAsString();

    // Save to database
    DBManager::getInstance().saveGameRecord(record);
}

std::vector<GameRecord> Game::getGameHistory(const std::string& username) {
    return DBManager::getInstance().getGameRecords(username);
}
