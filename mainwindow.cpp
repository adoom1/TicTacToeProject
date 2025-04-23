#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QMenu>
#include <QDebug>
#include <QTimer>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QHeaderView> // Added missing include for QHeaderView

// Implementation of DifficultyDialog
DifficultyDialog::DifficultyDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Select AI Difficulty");

    setStyleSheet(
        "QDialog { background-color: #ecf0f1; }"
        "QLabel { font-size: 16px; color: #2c3e50; padding: 5px; }"
        "QComboBox { "
        "   font-size: 14px; padding: 5px; border: 1px solid #bdc3c7; "
        "   border-radius: 4px; background-color: white; "
        "   selection-background-color: #3498db; min-width: 200px; "
        "}"
        "QPushButton { "
        "   background-color: #3498db; color: white; "
        "   padding: 6px 12px; border-radius: 4px; "
        "   font-weight: bold; min-width: 80px; "
        "}"
        "QPushButton:hover { background-color: #2980b9; }"
        );

    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *label = new QLabel("Select AI Difficulty Level:", this);
    difficultyComboBox = new QComboBox(this);
    difficultyComboBox->addItem("Easy", static_cast<int>(AIDifficulty::EASY));
    difficultyComboBox->addItem("Medium", static_cast<int>(AIDifficulty::MEDIUM));
    difficultyComboBox->addItem("Hard", static_cast<int>(AIDifficulty::HARD));
    difficultyComboBox->addItem("Impossible", static_cast<int>(AIDifficulty::IMPOSSIBLE));

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    layout->addWidget(label);
    layout->addWidget(difficultyComboBox);
    layout->addWidget(buttonBox);
    layout->setContentsMargins(20, 20, 20, 20);
    layout->setSpacing(15);
}
AIDifficulty DifficultyDialog::getSelectedDifficulty() const {
    return static_cast<AIDifficulty>(difficultyComboBox->currentData().toInt());
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), isPlayingAI(false), currentDifficulty(AIDifficulty::MEDIUM)
{
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    setupLoginUI();
    setupGameUI();
    setupHistoryUI();
    setupMenusAndToolbars();
    connectSignalsAndSlots();

    // Start with login screen
    stackedWidget->setCurrentWidget(loginWidget);

    resize(500, 600);
}

MainWindow::~MainWindow()
{
    // Clean up code here
}

void MainWindow::setupLoginUI() {
    loginWidget = new QWidget();
    loginWidget->setStyleSheet(
        "QWidget { background-color: #ecf0f1; }"
        "QLabel { color: #2c3e50; }"
        "QLineEdit { "
        "   padding: 8px; border: 1px solid #bdc3c7; "
        "   border-radius: 4px; background-color: white; "
        "}"
        "QPushButton { "
        "   background-color: #3498db; color: white; "
        "   padding: 8px 16px; border-radius: 4px; "
        "   font-weight: bold; min-width: 100px; "
        "}"
        "QPushButton:hover { background-color: #2980b9; }"
        );

    QVBoxLayout *layout = new QVBoxLayout(loginWidget);

    QLabel *titleLabel = new QLabel("Advanced Tic Tac Toe");
    titleLabel->setStyleSheet("font-size: 32px; font-weight: bold; color: #3498db;");
    titleLabel->setAlignment(Qt::AlignCenter);

    QWidget *formWidget = new QWidget();
    formWidget->setStyleSheet("background-color: white; border-radius: 10px; padding: 20px;");
    QFormLayout *formLayout = new QFormLayout(formWidget);

    usernameInput = new QLineEdit();
    passwordInput = new QLineEdit();
    passwordInput->setEchoMode(QLineEdit::Password);

    formLayout->addRow("Username:", usernameInput);
    formLayout->addRow("Password:", passwordInput);
    formLayout->setSpacing(15);
    formLayout->setContentsMargins(20, 20, 20, 20);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    loginButton = new QPushButton("Login");
    signupButton = new QPushButton("Sign Up");
    signupButton->setStyleSheet(
        "background-color: #2ecc71; color: white; "
        "padding: 8px 16px; border-radius: 4px; "
        "font-weight: bold; min-width: 100px;"
        );
    signupButton->setStyleSheet("background-color: #2ecc71;");

    buttonLayout->addWidget(loginButton);
    buttonLayout->addWidget(signupButton);
    buttonLayout->setSpacing(15);

    layout->addWidget(titleLabel);
    layout->addSpacing(30);
    layout->addWidget(formWidget);
    layout->addSpacing(20);
    layout->addLayout(buttonLayout);
    layout->setAlignment(buttonLayout, Qt::AlignCenter);
    layout->addStretch();
    layout->setContentsMargins(40, 40, 40, 40);

    stackedWidget->addWidget(loginWidget);
}

void MainWindow::setupGameUI()
{
    gameWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(gameWidget);

    statusLabel = new QLabel("Player X's turn");
    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setStyleSheet(
        "font-size: 24px; font-weight: bold; color: #2c3e50; "
        "background-color: #ecf0f1; padding: 10px; "
        "border: 1px solid #bdc3c7; border-radius: 5px;"
        );

    difficultyLabel = new QLabel("");
    difficultyLabel->setAlignment(Qt::AlignCenter);
    difficultyLabel->setStyleSheet(
        "font-size: 16px; color: #7f8c8d; "
        "background-color: #ecf0f1; padding: 5px; "
        "border: 1px solid #bdc3c7; border-radius: 5px;"
        );

    // In MainWindow::setupGameUI()
    QWidget *boardWidget = new QWidget();
    boardWidget->setStyleSheet(
        "background-color: #34495e; padding: 20px; border-radius: 15px;"
        );
    boardLayout = new QGridLayout(boardWidget);
    boardLayout->setSpacing(10);

    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            boardButtons[row][col] = new QPushButton("");
            boardButtons[row][col]->setFixedSize(120, 120); // Slightly larger buttons
            boardButtons[row][col]->setStyleSheet(
                "font-size: 40px; font-weight: bold; "
                "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #f5f5f5, stop:1 #e0e0e0); "
                "border: 1px solid #bdc3c7; border-radius: 10px;"
                );
            boardButtons[row][col]->setProperty("row", row);
            boardButtons[row][col]->setProperty("col", col);

            boardLayout->addWidget(boardButtons[row][col], row, col);
        }
    }
    boardLayout->setSpacing(10); // Increase spacing between cells

    layout->addWidget(statusLabel);
    layout->addWidget(difficultyLabel);
    layout->addWidget(boardWidget);
    layout->setAlignment(boardWidget, Qt::AlignCenter);

    stackedWidget->addWidget(gameWidget);
}

void MainWindow::setupHistoryUI() {
    historyWidget = new QWidget();
    historyWidget->setStyleSheet(
        "QWidget { background-color: #ecf0f1; }"
        "QLabel { color: #2c3e50; }"
        "QTableView { "
        "   background-color: white; alternate-background-color: #f5f5f5; "
        "   border: 1px solid #bdc3c7; border-radius: 5px; "
        "   gridline-color: #d0d0d0; "
        "}"
        "QHeaderView::section { "
        "   background-color: #3498db; color: white; "
        "   padding: 5px; border: 1px solid #2980b9; "
        "   font-weight: bold; "
        "}"
        "QPushButton { "
        "   background-color: #3498db; color: white; "
        "   padding: 8px 16px; border-radius: 4px; "
        "   font-weight: bold; min-width: 150px; "
        "}"
        "QPushButton:hover { background-color: #2980b9; }"
        );

    QVBoxLayout *layout = new QVBoxLayout(historyWidget);

    QLabel *titleLabel = new QLabel("Game History");
    titleLabel->setStyleSheet("font-size: 28px; font-weight: bold; color: #3498db;");
    titleLabel->setAlignment(Qt::AlignCenter);

    historyTableView = new QTableView();
    historyModel = new GameHistoryModel(this);
    historyTableView->setModel(historyModel);
    historyTableView->setAlternatingRowColors(true);
    historyTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    historyTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    historyTableView->horizontalHeader()->setStretchLastSection(true);
    historyTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    historyTableView->verticalHeader()->setVisible(false);

    QPushButton *backButton = new QPushButton("Back to Game");

    layout->addWidget(titleLabel);
    layout->addSpacing(15);
    layout->addWidget(historyTableView);
    layout->addSpacing(15);
    layout->addWidget(backButton);
    layout->setAlignment(backButton, Qt::AlignCenter);
    layout->setContentsMargins(20, 20, 20, 20);

    connect(backButton, &QPushButton::clicked, [this]() {
        stackedWidget->setCurrentWidget(gameWidget);
    });

    stackedWidget->addWidget(historyWidget);
}

void MainWindow::setupMenusAndToolbars()
{
    // Create menu bar
    mainMenuBar = menuBar(); // Use QMainWindow::menuBar()
    QMenu *gameMenu = mainMenuBar->addMenu("Game");
    QMenu *viewMenu = mainMenuBar->addMenu("View");
    QMenu *accountMenu = mainMenuBar->addMenu("Account");

    // Create actions
    newGameAction = new QAction("New Game", this);
    viewHistoryAction = new QAction("View History", this);
    playAIAction = new QAction("Play vs AI", this);
    playHumanAction = new QAction("Play vs Human", this);
    logoutAction = new QAction("Logout", this);

    // Add actions to menus
    gameMenu->addAction(newGameAction);
    gameMenu->addAction(playAIAction);
    gameMenu->addAction(playHumanAction);
    viewMenu->addAction(viewHistoryAction);
    accountMenu->addAction(logoutAction);

    // Setup toolbar
    toolBar = addToolBar("Main Toolbar");
    toolBar->addAction(newGameAction);
    toolBar->addAction(viewHistoryAction);
    toolBar->addAction(logoutAction);

    // Initially disable game-related actions until login
    newGameAction->setEnabled(false);
    viewHistoryAction->setEnabled(false);
    playAIAction->setEnabled(false);
    playHumanAction->setEnabled(false);
    logoutAction->setEnabled(false);
}

void MainWindow::connectSignalsAndSlots()
{
    // Login/signup connections
    connect(loginButton, &QPushButton::clicked, this, &MainWindow::handleLoginButtonClicked);
    connect(signupButton, &QPushButton::clicked, this, &MainWindow::handleSignupButtonClicked);

    // Game board connections
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            connect(boardButtons[row][col], &QPushButton::clicked, this, &MainWindow::handleBoardButtonClicked);
        }
    }

    // Menu action connections
    connect(newGameAction, &QAction::triggered, this, &MainWindow::handleNewGameAction);
    connect(viewHistoryAction, &QAction::triggered, this, &MainWindow::handleViewHistoryAction);
    connect(playAIAction, &QAction::triggered, this, &MainWindow::handlePlayAIAction);
    connect(playHumanAction, &QAction::triggered, this, &MainWindow::handlePlayHumanAction);
    connect(logoutAction, &QAction::triggered, this, &MainWindow::handleLogoutAction);
}

void MainWindow::handleLoginButtonClicked()
{
    QString username = usernameInput->text();
    QString password = passwordInput->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Login Error", "Username and password cannot be empty");
        return;
    }

    if (user.login(username.toStdString(), password.toStdString())) {
        currentUsername = username;
        resetBoard();
        stackedWidget->setCurrentWidget(gameWidget);

        // Enable game-related actions
        newGameAction->setEnabled(true);
        viewHistoryAction->setEnabled(true);
        playAIAction->setEnabled(true);
        playHumanAction->setEnabled(true);
        logoutAction->setEnabled(true);

        historyModel->loadHistory(currentUsername);
        statusLabel->setText("Player X's turn");
        difficultyLabel->setText("");
    } else {
        QMessageBox::warning(this, "Login Error", "Invalid username or password");
    }
}

void MainWindow::handleSignupButtonClicked()
{
    QString username = usernameInput->text();
    QString password = passwordInput->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Signup Error", "Username and password cannot be empty");
        return;
    }

    if (user.signup(username.toStdString(), password.toStdString())) {
        QMessageBox::information(this, "Signup Success", "Account created successfully! You can now login.");
        usernameInput->clear();
        passwordInput->clear();
    }
}

void MainWindow::handleBoardButtonClicked() {
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    int row = clickedButton->property("row").toInt();
    int col = clickedButton->property("col").toInt();

    if (game.makeMove(row, col)) {
        updateGameBoard();

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

        game.switchPlayer();
        statusLabel->setText(QString("Player %1's turn").arg(game.getCurrentPlayer()));

        // If playing against AI and it's AI's turn (O), make AI move
        if (isPlayingAI && game.getCurrentPlayer() == 'O') {
            QTimer::singleShot(500, this, &MainWindow::processAIMove);
        }
    }
}
void MainWindow::processAIMove() {
    // Apply AI move based on current difficulty
    game.makeAIMove();
    updateGameBoard();

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

    game.switchPlayer();
    statusLabel->setText(QString("Player %1's turn").arg(game.getCurrentPlayer()));
}

void MainWindow::handleNewGameAction() {
    resetBoard();
    if (isPlayingAI) {
        game.setAIDifficulty(currentDifficulty);
        updateDifficultyLabel();
    }
}

void MainWindow::handleViewHistoryAction() {
    historyModel->loadHistory(currentUsername);
    stackedWidget->setCurrentWidget(historyWidget);
}

void MainWindow::handlePlayAIAction() {
    showDifficultySelector();
    isPlayingAI = true;
    resetBoard();
    updateDifficultyLabel();
}

void MainWindow::handlePlayHumanAction() {
    isPlayingAI = false;
    resetBoard();
    difficultyLabel->setText("");
}

void MainWindow::handleLogoutAction() {
    currentUsername = "";
    usernameInput->clear();
    passwordInput->clear();
    stackedWidget->setCurrentWidget(loginWidget);

    // Disable game-related actions
    newGameAction->setEnabled(false);
    viewHistoryAction->setEnabled(false);
    playAIAction->setEnabled(false);
    playHumanAction->setEnabled(false);
    logoutAction->setEnabled(false);
}

void MainWindow::updateGameBoard() {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            char value = game.getBoardValue(row, col);
            boardButtons[row][col]->setText(QString(value));

            // Updated styling with gradient background and rounded corners
            if (value == 'X') {
                boardButtons[row][col]->setStyleSheet(
                    "font-size: 40px; font-weight: bold; color: #3498db; "
                    "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #f0f9ff, stop:1 #d6eaf8); "
                    "border: 2px solid #3498db; border-radius: 10px;"
                    );
            } else if (value == 'O') {
                boardButtons[row][col]->setStyleSheet(
                    "font-size: 40px; font-weight: bold; color: #e74c3c; "
                    "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #fff5f5, stop:1 #fdedec); "
                    "border: 2px solid #e74c3c; border-radius: 10px;"
                    );
            } else {
                // Empty cell styling
                boardButtons[row][col]->setStyleSheet(
                    "font-size: 40px; font-weight: bold; "
                    "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #f5f5f5, stop:1 #e0e0e0); "
                    "border: 1px solid #bdc3c7; border-radius: 10px;"
                    );
            }
        }
    }
}

// Fixed: Moved these methods outside of updateGameBoard()
void MainWindow::displayGameResult(const QString& winner) {
    QString result;
    QString styleSheet;

    if (isPlayingAI) {
        // AI mode
        if (winner == "X") {
            result = QString("%1 wins!").arg(currentUsername);
            styleSheet = "color: #3498db; font-weight: bold;"; // Blue for player X
        } else if (winner == "O") {
            result = "AI wins!";
            styleSheet = "color: #e74c3c; font-weight: bold;"; // Red for AI/O
        } else {
            result = "It's a draw!";
            styleSheet = "color: #7f8c8d; font-weight: bold;"; // Grey for draw
        }
    } else {
        // Human vs Human mode
        if (winner == "X") {
            result = QString("Player %1 wins!").arg(winner);
            styleSheet = "color: #3498db; font-weight: bold;";
        } else if (winner == "O") {
            result = QString("Player %1 wins!").arg(winner);
            styleSheet = "color: #e74c3c; font-weight: bold;";
        } else {
            result = "It's a draw!";
            styleSheet = "color: #7f8c8d; font-weight: bold;";
        }
    }

    statusLabel->setText(result);
    statusLabel->setStyleSheet(
        "font-size: 24px; " + styleSheet +
        "background-color: #ecf0f1; padding: 10px; "
        "border: 1px solid #bdc3c7; border-radius: 5px;"
        );

    // Disable all board buttons
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            boardButtons[row][col]->setEnabled(false);
        }
    }

    QMessageBox msgBox;
    msgBox.setWindowTitle("Game Over");
    msgBox.setText(result);
    msgBox.setStyleSheet(
        "QMessageBox { background-color: #ecf0f1; }"
        "QMessageBox QLabel { font-size: 16px; " + styleSheet + " }"
                       "QMessageBox QPushButton { "
                       "   background-color: #3498db; color: white; "
                       "   padding: 6px 12px; border-radius: 4px; "
                       "   font-weight: bold; min-width: 80px; "
                       "}"
                       "QMessageBox QPushButton:hover { background-color: #2980b9; }"
        );
    msgBox.exec();
}

void MainWindow::saveGameToHistory(const QString& winner) {
    QString result;
    QString opponent = isPlayingAI ? "AI" : "Human";

    if (isPlayingAI) {
        // AI mode
        if (winner == "X") {
            result = QString("%1 won").arg(currentUsername);
        } else if (winner == "O") {
            result = "AI won";
        } else {
            result = "Draw";
        }
    } else {
        // Human vs Human mode
        if (winner == "X") {
            result = QString("%1 won").arg(currentUsername);
        } else if (winner == "O") {
            result = "Guest won";
        } else {
            result = "Draw";
        }
    }

    game.saveGame(currentUsername.toStdString(), result.toStdString(), opponent.toStdString());
    historyModel->loadHistory(currentUsername);
}

void MainWindow::resetBoard() {
    game = Game(); // Create a new game instance

    // Reset all buttons
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            boardButtons[row][col]->setText("");
            boardButtons[row][col]->setStyleSheet("font-size: 32px; font-weight: bold;");
            boardButtons[row][col]->setEnabled(true);
        }
    }

    statusLabel->setText("Player X's turn");

    // If playing AI, set the difficulty
    if (isPlayingAI) {
        game.setAIDifficulty(currentDifficulty);
    }
}

void MainWindow::showDifficultySelector() {
    DifficultyDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        currentDifficulty = dialog.getSelectedDifficulty();
        game.setAIDifficulty(currentDifficulty);
    }
}

void MainWindow::updateDifficultyLabel() {
    if (!isPlayingAI) {
        difficultyLabel->setText("");
        return;
    }

    QString difficultyText;
    QString colorStyle;

    switch (currentDifficulty) {
    case AIDifficulty::EASY:
        difficultyText = "AI Difficulty: Easy";
        colorStyle = "color: #27ae60;"; // Green for easy
        break;
    case AIDifficulty::MEDIUM:
        difficultyText = "AI Difficulty: Medium";
        colorStyle = "color: #f39c12;"; // Orange for medium
        break;
    case AIDifficulty::HARD:
        difficultyText = "AI Difficulty: Hard";
        colorStyle = "color: #e74c3c;"; // Red for hard
        break;
    case AIDifficulty::IMPOSSIBLE:
        difficultyText = "AI Difficulty: Impossible";
        colorStyle = "color: #8e44ad;"; // Purple for impossible
        break;
    }

    difficultyLabel->setText(difficultyText);
    difficultyLabel->setStyleSheet(
        "font-size: 16px; " + colorStyle +
        "background-color: #ecf0f1; padding: 5px; "
        "border: 1px solid #bdc3c7; border-radius: 5px; font-weight: bold;"
        );
}
