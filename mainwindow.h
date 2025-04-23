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
#include <QComboBox>
#include <QDialog>
#include "Game.h"
#include "User.h"
#include "GameHistoryModel.h"

class DifficultyDialog : public QDialog {
    Q_OBJECT

public:
    explicit DifficultyDialog(QWidget *parent = nullptr);
    AIDifficulty getSelectedDifficulty() const;

private:
    QComboBox *difficultyComboBox;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleLoginButtonClicked();
    void handleSignupButtonClicked();
    void handleBoardButtonClicked();
    void handleNewGameAction();
    void handleViewHistoryAction();
    void handlePlayAIAction();
    void handlePlayHumanAction();
    void handleLogoutAction();
    void updateGameBoard();
    void displayGameResult(const QString& result);
    void saveGameToHistory(const QString& result);

private:
    // Stacked widget for different screens
    QStackedWidget *stackedWidget;

    // Login widgets
    QWidget *loginWidget;
    QLineEdit *usernameInput;
    QLineEdit *passwordInput;
    QPushButton *loginButton;
    QPushButton *signupButton;

    // Game widgets
    QWidget *gameWidget;
    QGridLayout *boardLayout;
    QPushButton *boardButtons[3][3];
    QLabel *statusLabel;
    QLabel *difficultyLabel;

    // History widgets
    QWidget *historyWidget;
    QTableView *historyTableView;
    GameHistoryModel *historyModel;

    // Menu and toolbar
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

    void setupLoginUI();
    void setupGameUI();
    void setupHistoryUI();
    void setupMenusAndToolbars();
    void connectSignalsAndSlots();
    void resetBoard();
    void processAIMove();
    void showDifficultySelector();
    void updateDifficultyLabel();
};

#endif // MAINWINDOW_H
