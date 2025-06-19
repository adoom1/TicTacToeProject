#include "MainWindow.h"
#include "BoardStateDelegate.h" // Include the new delegate header
#include "playerchoicedialog.h" // Include the new PlayerChoiceDialog header
#include "difficultyselector.h" // NEW: Include the new DifficultyDialog header
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QMenu>
#include <QDebug>
#include <QTimer>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QHeaderView>

// The implementations of DifficultyDialog and PlayerChoiceDialog
// are now in their respective .cpp files (difficultyselector.cpp and playerchoicedialog.cpp)
// so they are removed from here.

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow()), // Initialize the ui object
    isPlayingAI(false), currentDifficulty(AIDifficulty::MEDIUM),
    playerMarkSelectedByHuman('X') // Initialize with a default
{
    ui->setupUi(this); // Set up the UI from the .ui file

    // Apply main window and central widget background color
    this->setStyleSheet("QMainWindow { background-color: #1a1a1a; }");
    ui->centralwidget->setStyleSheet("QWidget#centralwidget { background-color: #1a1a1a; }"); // Ensure central widget is black

    // Assign pointers to widgets defined in the .ui file
    stackedWidget = ui->stackedWidget;
    loginWidget = ui->loginWidget;
    usernameInput = ui->usernameInput;
    passwordInput = ui->passwordInput;
    loginButton = ui->loginButton;
    signupButton = ui->signupButton;

    gameWidget = ui->gameWidget;
    boardWidget = ui->boardWidget;
    statusLabel = ui->statusLabel;
    difficultyLabel = ui->difficultyLabel;

    // Assign the board buttons using the object names from the UI file
    // AND set properties here for game logic
    boardButtons[0][0] = ui->boardButtons_0_0;
    boardButtons[0][1] = ui->boardButtons_0_1;
    boardButtons[0][2] = ui->boardButtons_0_2;
    boardButtons[1][0] = ui->boardButtons_1_0;
    boardButtons[1][1] = ui->boardButtons_1_1;
    boardButtons[1][2] = ui->boardButtons_1_2;
    boardButtons[2][0] = ui->boardButtons_2_0;
    boardButtons[2][1] = ui->boardButtons_2_1;
    boardButtons[2][2] = ui->boardButtons_2_2;

    // Set row/col properties for each button explicitly after assignment
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            boardButtons[r][c]->setProperty("row", r);
            boardButtons[r][c]->setProperty("col", c);
        }
    }


    newGameButtonUI = ui->newGameButtonUI;
    playAIButtonUI = ui->playAIButtonUI;
    playHumanButtonUI = ui->playHumanButtonUI;
    viewHistoryButtonUI = ui->viewHistoryButtonUI;
    logoutButtonUI = ui->logoutButtonUI;

    historyWidget = ui->historyWidget;
    historyTableView = ui->historyTableView;
    historyModel = new GameHistoryModel(this);
    historyTableView->setModel(historyModel);
    boardStateDelegate = new BoardStateDelegate(this);
    historyTableView->setItemDelegateForColumn(3, boardStateDelegate);
    historyTableView->setAlternatingRowColors(true);
    historyTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    historyTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    historyTableView->horizontalHeader()->setStretchLastSection(true);
    historyTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    historyTableView->verticalHeader()->setVisible(false);
    historyTableView->setWordWrap(true);
    historyTableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);


    // Assign menu and toolbar components
    mainMenuBar = ui->menubar;
    toolBar = ui->toolBar;
    newGameAction = ui->actionNew_Game;
    viewHistoryAction = ui->actionView_History;
    playAIAction = ui->actionPlay_vs_AI;
    playHumanAction = ui->actionPlay_vs_Human;
    logoutAction = ui->actionLogout;

    connectSignalsAndSlots();

    // Start with login screen
    stackedWidget->setCurrentWidget(loginWidget); // Use assigned pointer

    // Apply initial styles (these can be moved to a .qss file or stay here)
    loginWidget->setStyleSheet(
        "QWidget { background-color: #1a1a1a; }" // Dark background
        "QLabel { font-family: 'Press Start 2P', monospace; color: #00ffff; text-shadow: 0 0 5px #00ffff; }" // Neon blue with glow
        "QLineEdit { "
        "   padding: 10px; border: 2px solid #ff00ff; " // Neon pink border
        "   border-radius: 5px; background-color: #333333; color: #00ff00; " // Dark background, neon green text
        "   font-family: 'Press Start 2P', monospace; font-size: 14px; text-shadow: 0 0 3px #00ff00; "
        "}"
        "QPushButton { "
        "   background-color: #8a2be2; color: white; " // Blue-violet
        "   padding: 10px 20px; border-radius: 8px; "
        "   font-family: 'Press Start 2P', monospace; font-weight: bold; min-width: 120px; "
        "   border: 2px solid #ff00ff; "
        "   box-shadow: 0 0 10px rgba(255, 0, 255, 0.7);" // Glow effect
        "}"
        "QPushButton:hover { background-color: #6a0dad; box-shadow: 0 0 15px rgba(255, 0, 255, 1); }"
        "QPushButton:pressed { background-color: #4b0082; }"
        );

    // Specific style for signup button
    signupButton->setStyleSheet(
        "background-color: #00cc00; color: white; " // Brighter green for signup
        "padding: 10px 20px; border-radius: 8px; "
        "font-family: 'Press Start 2P', monospace; font-weight: bold; min-width: 120px;"
        "border: 2px solid #00ff00; " // Neon green border
        "box-shadow: 0 0 10px rgba(0, 255, 0, 0.7);"
        );

    // Apply specific style for New Game button (green theme)
    newGameButtonUI->setStyleSheet(
        "QPushButton { "
        "   background-color: #00cc00; color: white; " // Bright green
        "   padding: 10px 20px; border-radius: 8px; "
        "   font-family: 'Press Start 2P', monospace; font-weight: bold; min-width: 120px;"
        "   border: 2px solid #00ff00; " // Neon green border
        "   box-shadow: 0 0 10px rgba(0, 255, 0, 0.7);"
        "}"
        "QPushButton:hover { background-color: #009900; box-shadow: 0 0 15px rgba(0, 255, 0, 1); }"
        "QPushButton:pressed { background-color: #006600; }"
        );

    // Common base style for most buttons
    QString commonButtonStyle =
        "QPushButton { "
        "   background-color: #8a2be2; color: white; " // Blue-violet
        "   padding: 10px 20px; border-radius: 8px; "
        "   font-family: 'Press Start 2P', monospace; font-weight: bold; min-width: 120px; "
        "   border: 2px solid #ff00ff; "
        "   box-shadow: 0 0 10px rgba(255, 0, 255, 0.7);"
        "}"
        "QPushButton:hover { background-color: #6a0dad; box-shadow: 0 0 15px rgba(255, 0, 255, 1); }"
        "QPushButton:pressed { background-color: #4b0082; }"
        ;

    // Apply common style to other action buttons
    playAIButtonUI->setStyleSheet(commonButtonStyle);
    playHumanButtonUI->setStyleSheet(commonButtonStyle);
    viewHistoryButtonUI->setStyleSheet(commonButtonStyle);
    loginButton->setStyleSheet(commonButtonStyle); // Apply to login button as well

    // Apply specific style for Logout button (red theme)
    logoutButtonUI->setStyleSheet(
        "QPushButton { "
        "   background-color: #cc0000; color: white; " // Red
        "   padding: 10px 20px; border-radius: 8px; "
        "   font-family: 'Press Start 2P', monospace; font-weight: bold; min-width: 120px; "
        "   border: 2px solid #ff00ff; " // Neon pink border (consistent border glow)
        "   box-shadow: 0 0 10px rgba(255, 0, 255, 0.7);"
        "}"
        "QPushButton:hover { background-color: #990000; box-shadow: 0 0 15px rgba(255, 0, 255, 1); }"
        "QPushButton:pressed { background-color: #660000; }"
        );

    // Initial styling for board buttons
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            boardButtons[row][col]->setStyleSheet(
                "font-family: 'Press Start 2P', monospace; font-size: 40px; font-weight: bold; "
                "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #1a1a1a, stop:1 #333333); "
                "border: 2px solid #00ff00; border-radius: 15px; " // Neon green border
                "color: #aaaaaa;" // Dim text color
                "box-shadow: 0 0 8px rgba(0, 255, 0, 0.5);"
                );
        }
    }

    // Set styling for history view
    historyWidget->setStyleSheet(
        "QWidget { background-color: #1a1a1a; }"
        "QLabel { font-family: 'Press Start 2P', monospace; color: #00ffff; text-shadow: 0 0 5px #00ffff; }"
        "QTableView { "
        "   background-color: #222222; alternate-background-color: #333333; " // Dark cells
        "   border: 2px solid #ff00ff; border-radius: 10px; " // Neon pink border
        "   gridline-color: #8a2be2; " // Purple grid lines
        "   font-family: 'Press Start 2P', monospace; font-size: 14px; color: #00ff00; " // Neon green text (Increased font size)
        "}"
        "QHeaderView::section { "
        "   background-color: #6a0dad; color: #00ffff; " // Darker purple header, neon blue text
        "   padding: 8px; border: 1px solid #ff00ff; "
        "   font-family: 'Press Start 2P', monospace; font-weight: bold; text-shadow: 0 0 3px #00ffff; "
        "}"
        "QPushButton { "
        "   background-color: #8a2be2; color: white; "
        "   padding: 10px 20px; border-radius: 8px; "
        "   font-family: 'Press Start 2P', monospace; font-weight: bold; min-width: 150px; "
        "   border: 2px solid #ff00ff; "
        "   box-shadow: 0 0 10px rgba(255, 0, 255, 0.7);"
        "}"
        "QPushButton:hover { background-color: #6a0dad; box-shadow: 0 0 15px rgba(255, 0, 255, 1); }"
        "QPushButton:pressed { background-color: #4b0082; }"
        );

    // Connect back button in history view
    connect(ui->backButton_history, &QPushButton::clicked, [this]() {
        stackedWidget->setCurrentWidget(gameWidget);
    });

    // Initially disable game-related actions until login
    newGameAction->setEnabled(false);
    viewHistoryAction->setEnabled(false);
    playAIAction->setEnabled(false);
    playHumanAction->setEnabled(false);
    logoutAction->setEnabled(false);
    // Also disable the new UI buttons until login
    newGameButtonUI->setEnabled(false);
    playAIButtonUI->setEnabled(false);
    playHumanButtonUI->setEnabled(false);
    viewHistoryButtonUI->setEnabled(false);
    logoutButtonUI->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui; // Clean up the ui object
}

void MainWindow::connectSignalsAndSlots()
{
    // Login/signup connections
    connect(ui->loginButton, &QPushButton::clicked, this, &MainWindow::handleLoginButtonClicked);
    connect(ui->signupButton, &QPushButton::clicked, this, &MainWindow::handleSignupButtonClicked);

    // Game board connections (Modified to use lambda to capture row/col)
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            // Use a lambda to capture row and col by value for each button
            connect(boardButtons[row][col], &QPushButton::clicked, this, [this, row, col]() {
                this->handleBoardButtonClickedFromLambda(row, col);
            });
        }
    }

    // Menu action connections (these will now primarily call the UI button handlers)
    // Connecting to new UI buttons' clicked signals which in turn call the handlers
    connect(ui->actionNew_Game, &QAction::triggered, ui->newGameButtonUI, &QPushButton::clicked);
    connect(ui->actionView_History, &QAction::triggered, ui->viewHistoryButtonUI, &QPushButton::clicked);
    connect(ui->actionPlay_vs_AI, &QAction::triggered, ui->playAIButtonUI, &QPushButton::clicked);
    connect(ui->actionPlay_vs_Human, &QAction::triggered, ui->playHumanButtonUI, &QPushButton::clicked);
    connect(ui->actionLogout, &QAction::triggered, ui->logoutButtonUI, &QPushButton::clicked);

    // Connect new UI buttons to existing handlers
    connect(ui->newGameButtonUI, &QPushButton::clicked, this, &MainWindow::handleNewGameAction);
    connect(ui->playAIButtonUI, &QPushButton::clicked, this, &MainWindow::handlePlayAIAction);
    connect(ui->playHumanButtonUI, &QPushButton::clicked, this, &MainWindow::handlePlayHumanAction);
    connect(ui->viewHistoryButtonUI, &QPushButton::clicked, this, &MainWindow::handleViewHistoryAction); // Connect new button
    connect(ui->logoutButtonUI, &QPushButton::clicked, this, &MainWindow::handleLogoutAction);           // Connect new button
}

// New slot to handle board button clicks from lambda, taking row and col directly
void MainWindow::handleBoardButtonClickedFromLambda(int row, int col) {
    if (game.makeMove(row, col)) {
        updateGameBoard();

        // Disable all buttons immediately after a valid player move
        for (int r = 0; r < 3; r++) {
            for (int c = 0; c < 3; c++) {
                boardButtons[r][c]->setEnabled(false);
            }
        }

        if (game.checkWin()) {
            displayGameResult(QString(game.getCurrentPlayer()));
            saveGameToHistory(QString(game.getCurrentPlayer()));
            return;
        }

        if (game.checkDraw()) {
            displayGameResult("Draw");
            saveGameToHistory("Draw");
            return;
        }

        game.switchPlayer(); // Switch to the next player's turn
        ui->statusLabel->setText(QString("Player %1's turn").arg(game.getCurrentPlayer()));
        // Reapply default status label style after reset
        ui->statusLabel->setStyleSheet(
            "font-family: 'Press Start 2P', monospace; font-size: 28px; font-weight: bold; color: #ffff00; " // Neon yellow
            "background-color: #333333; padding: 10px; "
            "border: 2px solid #ff00ff; border-radius: 8px; text-shadow: 0 0 5px #ffff00;"
            );


        // If playing against AI and it's AI's turn (opposite of human's selected mark)
        // Check if the current player (after switch) is NOT the human's chosen mark.
        if (isPlayingAI && game.getCurrentPlayer() != playerMarkSelectedByHuman) {
            QTimer::singleShot(500, this, &MainWindow::processAIMove);
        }
        else {
            // Re-enable buttons for the human player's turn
            for (int r = 0; r < 3; r++) {
                for (int c = 0; c < 3; c++) {
                    if (game.getBoardValue(r, c) == ' ') {
                        boardButtons[r][c]->setEnabled(true);
                    }
                }
            }
        }
    }
}


void MainWindow::handleLoginButtonClicked()
{
    QString username = ui->usernameInput->text();
    QString password = ui->passwordInput->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Login Error", "Username and password cannot be empty");
        return;
    }

    if (user.login(username.toStdString(), password.toStdString())) {
        currentUsername = username;
        stackedWidget->setCurrentWidget(gameWidget); // Use assigned pointer

        // Enable game-related actions in menu
        ui->actionNew_Game->setEnabled(true);
        ui->actionView_History->setEnabled(true);
        ui->actionPlay_vs_AI->setEnabled(true);
        ui->actionPlay_vs_Human->setEnabled(true);
        ui->actionLogout->setEnabled(true);
        // Enable UI buttons
        ui->newGameButtonUI->setEnabled(true);
        ui->playAIButtonUI->setEnabled(true);
        ui->playHumanButtonUI->setEnabled(true);
        ui->viewHistoryButtonUI->setEnabled(true);
        ui->logoutButtonUI->setEnabled(true);


        historyModel->loadHistory(currentUsername);
        // Set initial welcome message with desired pink styling
        ui->statusLabel->setText("Welcome! Choose a game mode below or from 'Game' menu.");
        ui->statusLabel->setStyleSheet(
            "font-family: 'Press Start 2P', monospace; font-size: 28px; font-weight: bold; "
            "color: #ff00ff; text-shadow: 0 0 5px #ff00ff;" // Neon pink with glow
            "background-color: #333333; padding: 10px; "
            "border: 2px solid #ff00ff; border-radius: 8px;" // Neon pink border
            );
        ui->difficultyLabel->setText(""); // This already clears it.

        // --- START OF CHANGE ---
        // Ensure a clean game state when logging in
        isPlayingAI = false; // Reset game mode to human vs human by default
        game = Game(); // Re-initialize game to clear board and reset current player to 'X'
        updateGameBoard(); // Update the visual board to reflect the empty state
        // --- END OF CHANGE ---

    } else {
        QMessageBox::warning(this, "Login Error", "Invalid username or password");
    }
}

void MainWindow::handleSignupButtonClicked()
{
    QString username = ui->usernameInput->text();
    QString password = ui->passwordInput->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Signup Error", "Username and password cannot be empty");
        return;
    }

    if (user.signup(username.toStdString(), password.toStdString())) {
        QMessageBox::information(this, "Signup Success", "Account created successfully! You can now login.");
        ui->usernameInput->clear();
        ui->passwordInput->clear();
    }
}

// Renamed handleBoardButtonClicked to handleBoardButtonClicked_Old for clarity, it's no longer used directly
void MainWindow::handleBoardButtonClicked() {
    // This function is no longer called directly from connectSignalsAndSlots,
    // as we are now using handleBoardButtonClickedFromLambda.
    // It's kept here as a placeholder in case any other part of your code
    // was still connecting to it, but it should ideally be removed.
}

void MainWindow::processAIMove() {
    // Apply AI move based on current difficulty
    game.makeAIMove();
    updateGameBoard();

    // After AI makes its move, re-enable the buttons for the human player
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (game.getBoardValue(r, c) == ' ') {
                boardButtons[r][c]->setEnabled(true);
            }
        }
    }

    if (game.checkWin()) {
        displayGameResult(QString(game.getCurrentPlayer()));
        saveGameToHistory(QString(game.getCurrentPlayer()));
        return;
    }

    if (game.checkDraw()) {
        displayGameResult("Draw");
        saveGameToHistory("Draw");
        return;
    }

    game.switchPlayer(); // Switch to the next player's turn (human's turn)
    ui->statusLabel->setText(QString("Player %1's turn").arg(game.getCurrentPlayer()));
    // Reapply default status label style after AI turn
    ui->statusLabel->setStyleSheet(
        "font-family: 'Press Start 2P', monospace; font-size: 28px; font-weight: bold; color: #ffff00; " // Neon yellow
        "background-color: #333333; padding: 10px; "
        "border: 2px solid #ff00ff; border-radius: 8px; text-shadow: 0 0 5px #ffff00;"
        );
}

void MainWindow::handleNewGameAction() {
    // This action now consistently leads to player choice, then game mode
    // It doesn't set isPlayingAI directly, as that is set by Play AI/Play Human actions.
    showPlayerChoiceSelector();
}

void MainWindow::handleViewHistoryAction() {
    historyModel->loadHistory(currentUsername);
    stackedWidget->setCurrentWidget(historyWidget);
}

void MainWindow::handlePlayAIAction() {
    isPlayingAI = true;
    showPlayerChoiceSelector(); // This will trigger resetBoard and then difficulty selection
}

void MainWindow::handlePlayHumanAction() {
    isPlayingAI = false;
    showPlayerChoiceSelector(); // This will trigger resetBoard
    // Difficulty label will be cleared in resetBoard
}

void MainWindow::handleLogoutAction() {
    currentUsername = "";
    ui->usernameInput->clear();
    ui->passwordInput->clear();
    stackedWidget->setCurrentWidget(loginWidget);

    // Disable game-related actions in menu and UI buttons
    newGameAction->setEnabled(false);
    viewHistoryAction->setEnabled(false);
    playAIAction->setEnabled(false);
    playHumanAction->setEnabled(false);
    logoutAction->setEnabled(false);

    newGameButtonUI->setEnabled(false);
    playAIButtonUI->setEnabled(false);
    playHumanButtonUI->setEnabled(false);
    viewHistoryButtonUI->setEnabled(false);
    logoutButtonUI->setEnabled(false);
}

void MainWindow::updateGameBoard() {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            char value = game.getBoardValue(row, col);
            boardButtons[row][col]->setText(QString(value));

            // Updated styling with gradient background and rounded corners
            if (value == 'X') {
                boardButtons[row][col]->setStyleSheet(
                    "font-family: 'Press Start 2P', monospace; font-size: 50px; font-weight: bold; color: #00ffff; " // Brighter neon blue for X
                    "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #005555, stop:1 #008888); " // Darker blue gradient
                    "border: 4px solid #00ffff; border-radius: 15px; " // Thicker neon blue border
                    "box-shadow: 0 0 15px rgba(0, 255, 255, 0.8);" // Stronger glow
                    );
            } else if (value == 'O') {
                boardButtons[row][col]->setStyleSheet(
                    "font-family: 'Press Start 2P', monospace; font-size: 50px; font-weight: bold; color: #ff00ff; " // Neon pink for O
                    "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #550055, stop:1 #880088); " // Darker pink gradient
                    "border: 4px solid #ff00ff; border-radius: 15px; " // Thicker neon pink border
                    "box-shadow: 0 0 15px rgba(255, 0, 255, 0.8);" // Stronger glow
                    );
            } else {
                // Empty cell styling
                boardButtons[row][col]->setStyleSheet(
                    "font-family: 'Press Start 2P', monospace; font-size: 40px; font-weight: bold; "
                    "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #1a1a1a, stop:1 #333333); "
                    "border: 2px solid #00ff00; border-radius: 15px; "
                    "color: #aaaaaa;" // Dim text color
                    "box-shadow: 0 0 8px rgba(0, 255, 0, 0.5);"
                    );
            }
        }
    }
}

void MainWindow::displayGameResult(const QString& winner) {
    QString result;
    QString styleSheet;

    if (winner == "Draw") {
        result = "IT'S A DRAW!";
        styleSheet = "color: #ffff00; text-shadow: 0 0 5px #ffff00;"; // Neon yellow for draw
    } else if (isPlayingAI) {
        // AI mode: Determine if human or AI won based on playerMarkSelectedByHuman
        if (winner.at(0).toLatin1() == playerMarkSelectedByHuman) {
            result = QString("%1 WINS!").arg(currentUsername.toUpper());
            styleSheet = "color: #00ffff; text-shadow: 0 0 5px #00ffff;"; // Neon blue for human player win
        } else {
            result = "AI WINS!";
            styleSheet = "color: #ff00ff; text-shadow: 0 0 5px #ff00ff;"; // Neon pink for AI win
        }
    } else {
        // Human vs Human mode: Winner is currentUsername if winner's mark matches human's chosen mark, else Guest
        if (winner.at(0).toLatin1() == playerMarkSelectedByHuman) {
            result = QString("%1 WINS!").arg(currentUsername.toUpper());
            styleSheet = "color: #00ffff; text-shadow: 0 0 5px #00ffff;";
        } else {
            result = "GUEST WINS!"; // This implies the other human player
            styleSheet = "color: #ff00ff; text-shadow: 0 0 5px #ff00ff;";
        }
    }

    ui->statusLabel->setText(result);
    ui->statusLabel->setStyleSheet(
        "font-family: 'Press Start 2P', monospace; font-size: 28px; font-weight: bold; " + styleSheet +
        "background-color: #333333; padding: 10px; "
        "border: 2px solid #ff00ff; border-radius: 8px;"
        );

    // Disable all board buttons
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            boardButtons[row][col]->setEnabled(false);
        }
    }

    QMessageBox msgBox;
    msgBox.setWindowTitle("GAME OVER!");
    msgBox.setText(result);
    msgBox.setStyleSheet(
        "QMessageBox { background-color: #1a1a1a; border: 2px solid #00ff00; border-radius: 10px; }"
        "QMessageBox QLabel { font-family: 'Press Start 2P', monospace; font-size: 20px; " + styleSheet + " }"
                       "QMessageBox QPushButton { "
                       "   background-color: #8a2be2; color: white; "
                       "   padding: 8px 16px; border-radius: 6px; "
                       "   font-family: 'Press Start 2P', monospace; font-weight: bold; min-width: 80px; "
                       "   border: 2px solid #ff00ff; box-shadow: 0 0 8px rgba(255, 0, 255, 0.7);"
                       "}"
                       "QMessageBox QPushButton:hover { background-color: #6a0dad; box-shadow: 0 0 12px rgba(255, 0, 255, 1); }"
        );
    msgBox.exec();
}

void MainWindow::saveGameToHistory(const QString& winner) {
    QString result;
    QString opponentString;

    // Determine opponent string based on game mode and difficulty
    if (isPlayingAI) {
        opponentString = "AI -- ";
        switch (currentDifficulty) {
        case AIDifficulty::EASY: opponentString += "Easy Mode"; break;
        case AIDifficulty::MEDIUM: opponentString += "Medium Mode"; break;
        case AIDifficulty::HARD: opponentString += "Hard Mode"; break;
        case AIDifficulty::IMPOSSIBLE: opponentString += "Impossible Mode"; break;
        default: opponentString += "Unknown Mode"; break; // Fallback
        }
    } else {
        opponentString = "Human";
    }


    if (winner == "Draw") {
        result = "Draw";
    } else if (isPlayingAI) {
        // AI mode: If winner mark is human's chosen mark, human won. Else AI won.
        if (winner.at(0).toLatin1() == playerMarkSelectedByHuman) {
            result = QString("%1 won").arg(currentUsername);
        } else {
            result = "AI won";
        }
    } else {
        // Human vs Human mode: If winner mark is human's chosen mark, current user won. Else Guest won.
        if (winner.at(0).toLatin1() == playerMarkSelectedByHuman) {
            result = QString("%1 won").arg(currentUsername);
        } else {
            result = "Guest won";
        }
    }

    game.saveGame(currentUsername.toStdString(), result.toStdString(), opponentString.toStdString());
    historyModel->loadHistory(currentUsername);
}

// Modified resetBoard to accept a starting player character (human's choice)
void MainWindow::resetBoard(char startingPlayer) {
    game = Game(); // Create a new game instance; Game constructor sets currentPlayer to 'X'
    playerMarkSelectedByHuman = startingPlayer; // Store the human's chosen mark for display/AI logic

    // Reset all buttons
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            boardButtons[row][col]->setText("");
            boardButtons[row][col]->setStyleSheet(
                "font-size: 40px; font-weight: bold; "
                "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #1a1a1a, stop:1 #333333); "
                "border: 2px solid #00ff00; border-radius: 15px; "
                "color: #aaaaaa;"
                );
            boardButtons[row][col]->setEnabled(true); // Ensure buttons are enabled at the start of a new game
        }
    }

    // Always clear difficulty label at the start of a new game, it will be set if AI is playing
    ui->difficultyLabel->setText("");


    // Handle initial turn and status label based on game mode and human's choice
    if (isPlayingAI) {
        // If playing AI, first show difficulty selector
        showDifficultySelector(); // This will block until user selects difficulty
            // currentDifficulty and game.aiDifficulty will be updated here.

        if (playerMarkSelectedByHuman == 'O') {
            // Human chose 'O', so AI (playing as 'X' since game always starts with 'X') should make the first move.
            ui->statusLabel->setText("AI (X)'s turn");
            ui->statusLabel->setStyleSheet(
                "font-family: 'Press Start 2P', monospace; font-size: 28px; font-weight: bold; color: #ff00ff; " // Neon pink for AI's turn
                "background-color: #333333; padding: 10px; "
                "border: 2px solid #ff00ff; border-radius: 8px; text-shadow: 0 0 5px #ff00ff;"
                );
            // Disable board buttons until AI makes its move to prevent quick human input
            for (int r = 0; r < 3; r++) {
                for (int c = 0; c < 3; c++) {
                    boardButtons[r][c]->setEnabled(false);
                }
            }
            // Trigger AI's first move AFTER difficulty has been set
            QTimer::singleShot(500, this, &MainWindow::processAIMove);
        } else {
            // Human chose 'X', human starts.
            ui->statusLabel->setText(QString("Player X's turn")); // Visually, it's X's turn to start
            ui->statusLabel->setStyleSheet(
                "font-family: 'Press Start 2P', monospace; font-size: 28px; font-weight: bold; color: #ffff00; " // Neon yellow
                "background-color: #333333; padding: 10px; "
                "border: 2px solid #ff00ff; border-radius: 8px; text-shadow: 0 0 5px #ffff00;"
                );
            // Buttons are already enabled by the initial loop
        }
    } else { // Playing Human vs Human
        ui->statusLabel->setText(QString("Player X's turn")); // Human vs Human always starts with X
        ui->statusLabel->setStyleSheet(
            "font-family: 'Press Start 2P', monospace; font-size: 28px; font-weight: bold; color: #ffff00; " // Neon yellow
            "background-color: #333333; padding: 10px; "
            "border: 2px solid #ff00ff; border-radius: 8px; text-shadow: 0 0 5px #ffff00;"
            );
        // Buttons are already enabled by the initial loop
    }
}

void MainWindow::showDifficultySelector() {
    DifficultyDialog dialog(this); // Instantiates the UI-based dialog
    if (dialog.exec() == QDialog::Accepted) {
        currentDifficulty = dialog.getSelectedDifficulty();
        game.setAIDifficulty(currentDifficulty);
        updateDifficultyLabel(); // Update the label after setting difficulty
    } else {
        // If difficulty dialog is cancelled, it means the user doesn't want to play AI.
        // We should revert to the login screen or a neutral state.
        // For simplicity, let's go back to the login screen if difficulty selection is cancelled.
        // You might want a more graceful handling, e.g., back to game mode selection.
        if (!user.isUserLoggedIn()) { // If not logged in, always revert to login
            stackedWidget->setCurrentWidget(loginWidget);
        } else { // If logged in, revert to game screen without starting a game
            ui->statusLabel->setText("AI game cancelled. Choose 'Game' to begin a new match.");
            ui->statusLabel->setStyleSheet(
                "font-family: 'Press Start 2P', monospace; font-size: 28px; font-weight: bold; color: #ffff00; "
                "background-color: #333333; padding: 10px; "
                "border: 2px solid #ff00ff; border-radius: 8px; text-shadow: 0 0 5px #ffff00;"
                );
            for (int r = 0; r < 3; r++) {
                for (int c = 0; c < 3; c++) {
                    boardButtons[r][c]->setEnabled(false); // Ensure board is disabled if game isn't started
                }
            }
        }
        isPlayingAI = false; // If player choice is cancelled, ensure AI mode is off
        ui->difficultyLabel->setText(""); // Also clear difficulty label
    }
}

void MainWindow::updateDifficultyLabel() {
    if (!isPlayingAI) {
        ui->difficultyLabel->setText(""); // Ensure it's cleared if not AI game
        return;
    }

    QString difficultyText;
    QString colorStyle;

    switch (currentDifficulty) {
    case AIDifficulty::EASY:
        difficultyText = "AI DIFFICULTY: EASY";
        colorStyle = "#00ff00"; // Neon Green
        break;
    case AIDifficulty::MEDIUM:
        difficultyText = "AI DIFFICULTY: MEDIUM";
        colorStyle = "#ffff00"; // Neon Yellow
        break;
    case AIDifficulty::HARD:
        difficultyText = "AI DIFFICULTY: HARD";
        colorStyle = "#ff00ff"; // Neon Pink
        break;
    case AIDifficulty::IMPOSSIBLE:
        difficultyText = "AI DIFFICULTY: IMPOSSIBLE";
        colorStyle = "#00ffff"; // Neon Blue
        break;
    }

    // Apply consistent styling with dynamic color
    ui->difficultyLabel->setText(difficultyText);
    ui->difficultyLabel->setStyleSheet(
        "font-family: 'Press Start 2P', monospace; font-size: 18px; font-weight: bold; "
        "color: " + colorStyle + "; "
                       "background-color: #333333; padding: 10px; " // Consistent padding with statusLabel
                       "border: 2px solid " + colorStyle + "; "
                       "border-radius: 8px; " // Consistent border-radius with statusLabel
                       "text-shadow: 0 0 5px " + colorStyle + ";" // Consistent text-shadow with statusLabel
        );
}

// Updated method to show the UI-based player choice dialog
void MainWindow::showPlayerChoiceSelector() {
    PlayerChoiceDialog dialog(this); // Now instantiates the UI-based dialog
    if (dialog.exec() == QDialog::Accepted) {
        char chosenPlayer = dialog.getSelectedPlayer();
        resetBoard(chosenPlayer); // Pass the chosen player to resetBoard
    } else {
        // If the user cancels the player choice, handle the state.
        // For example, if not logged in, go back to login screen.
        if (!user.isUserLoggedIn()) {
            stackedWidget->setCurrentWidget(loginWidget);
        } else {
            // If logged in and cancelled, perhaps just remain on game screen without starting new game
            ui->statusLabel->setText("Game not started. Choose 'Game' to begin.");
            // Reapply default status label style
            ui->statusLabel->setStyleSheet(
                "font-family: 'Press Start 2P', monospace; font-size: 28px; font-weight: bold; color: #ffff00; " // Neon yellow
                "background-color: #333333; padding: 10px; "
                "border: 2px solid #ff00ff; border-radius: 8px; text-shadow: 0 0 5px #ffff00;"
                );
            // Also ensure the board buttons are enabled for a potential new game start if they were disabled before
            for (int r = 0; r < 3; r++) {
                for (int c = 0; c < 3; c++) {
                    boardButtons[r][c]->setEnabled(true);
                }
            }
        }
        isPlayingAI = false; // If player choice is cancelled, ensure AI mode is off
        ui->difficultyLabel->setText(""); // Also clear difficulty label
    }
}


