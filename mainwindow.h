// MainWindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QStackedWidget>
#include <QLineEdit>
#include <QMessageBox>
#include <QTableView>
#include <QStatusBar>
#include <QToolBar>
#include <QMenuBar>
#include <QAction>
#include <QComboBox> // Still needed for QComboBox if you use it directly
#include <QDialog>
#include <QDialogButtonBox> // Still needed for QDialogButtonBox if you use it directly
#include <QButtonGroup>

#include "Game.h"
#include "User.h"
#include "GameHistoryModel.h"
#include "ui_mainwindow.h" // Include the generated UI header for MainWindow

// Forward declarations for external UI-based dialogs
class BoardStateDelegate;
class PlayerChoiceDialog; // Now a standalone UI-based class
class DifficultyDialog;   // NEW: Now a standalone UI-based class

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleLoginButtonClicked();
    void handleSignupButtonClicked();
    void handleBoardButtonClicked(); // Keep this declared, even if it's currently unused (placeholder)
    void handleBoardButtonClickedFromLambda(int row, int col);
    void handleNewGameAction();
    void handleViewHistoryAction();
    void handlePlayAIAction();
    void handlePlayHumanAction();
    void handleLogoutAction();
    void updateGameBoard();
    void displayGameResult(const QString& result);
    void saveGameToHistory(const QString& result);

private:
    Ui::MainWindow *ui; // Pointer to the generated UI class for MainWindow

    // These members will now point to widgets loaded from the UI file
    QStackedWidget *stackedWidget;
    QWidget *loginWidget;
    QLineEdit *usernameInput;
    QLineEdit *passwordInput;
    QPushButton *loginButton;
    QPushButton *signupButton;

    QWidget *gameWidget;
    QWidget *boardWidget;
    QPushButton *boardButtons[3][3]; // Keep this array for easy access to board buttons
    QLabel *statusLabel;
    QLabel *difficultyLabel;
    QPushButton *newGameButtonUI;
    QPushButton *playAIButtonUI;
    QPushButton *playHumanButtonUI;
    QPushButton *viewHistoryButtonUI;
    QPushButton *logoutButtonUI;


    QWidget *historyWidget;
    QTableView *historyTableView;
    GameHistoryModel *historyModel;
    BoardStateDelegate *boardStateDelegate;

    QMenuBar *mainMenuBar;
    QToolBar *toolBar;
    QAction *newGameAction;
    QAction *viewHistoryAction;
    QAction *playAIAction;
    QAction *playHumanAction;
    QAction *logoutAction;

    // Game logic
    Game game;
    User user;
    QString currentUsername;
    bool isPlayingAI;
    AIDifficulty currentDifficulty;
    char playerMarkSelectedByHuman; // Stores the human player's chosen mark (X or O)

    void connectSignalsAndSlots();
    void resetBoard(char startingPlayer = 'X');
    void processAIMove();
    void showDifficultySelector();
    void updateDifficultyLabel();
    void showPlayerChoiceSelector();
};

#endif // MAINWINDOW_H
