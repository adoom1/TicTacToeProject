/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew_Game;
    QAction *actionView_History;
    QAction *actionPlay_vs_AI;
    QAction *actionPlay_vs_Human;
    QAction *actionLogout;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_main;
    QStackedWidget *stackedWidget;
    QWidget *loginWidget;
    QVBoxLayout *verticalLayout_login;
    QLabel *titleLabel_login;
    QSpacerItem *verticalSpacer_login_1;
    QWidget *formWidget;
    QFormLayout *formLayout;
    QLabel *label_username;
    QLineEdit *usernameInput;
    QLabel *label_password;
    QLineEdit *passwordInput;
    QSpacerItem *verticalSpacer_login_2;
    QHBoxLayout *buttonLayout_login;
    QPushButton *loginButton;
    QPushButton *signupButton;
    QSpacerItem *verticalSpacer_login_3;
    QWidget *gameWidget;
    QVBoxLayout *verticalLayout_game;
    QLabel *statusLabel;
    QLabel *difficultyLabel;
    QWidget *boardWidget;
    QGridLayout *boardLayout;
    QPushButton *boardButtons_0_0;
    QPushButton *boardButtons_0_1;
    QPushButton *boardButtons_0_2;
    QPushButton *boardButtons_1_0;
    QPushButton *boardButtons_1_1;
    QPushButton *boardButtons_1_2;
    QPushButton *boardButtons_2_0;
    QPushButton *boardButtons_2_1;
    QPushButton *boardButtons_2_2;
    QHBoxLayout *gameControlLayout;
    QPushButton *newGameButtonUI;
    QPushButton *playAIButtonUI;
    QPushButton *playHumanButtonUI;
    QPushButton *viewHistoryButtonUI;
    QPushButton *logoutButtonUI;
    QWidget *historyWidget;
    QVBoxLayout *verticalLayout_history;
    QLabel *titleLabel_history;
    QSpacerItem *verticalSpacer_history_1;
    QTableView *historyTableView;
    QSpacerItem *verticalSpacer_history_2;
    QPushButton *backButton_history;
    QMenuBar *menubar;
    QMenu *menuGame;
    QMenu *menuView;
    QMenu *menuAccount;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(500, 600);
        actionNew_Game = new QAction(MainWindow);
        actionNew_Game->setObjectName("actionNew_Game");
        actionView_History = new QAction(MainWindow);
        actionView_History->setObjectName("actionView_History");
        actionPlay_vs_AI = new QAction(MainWindow);
        actionPlay_vs_AI->setObjectName("actionPlay_vs_AI");
        actionPlay_vs_Human = new QAction(MainWindow);
        actionPlay_vs_Human->setObjectName("actionPlay_vs_Human");
        actionLogout = new QAction(MainWindow);
        actionLogout->setObjectName("actionLogout");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_main = new QVBoxLayout(centralwidget);
        verticalLayout_main->setObjectName("verticalLayout_main");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        loginWidget = new QWidget();
        loginWidget->setObjectName("loginWidget");
        verticalLayout_login = new QVBoxLayout(loginWidget);
        verticalLayout_login->setObjectName("verticalLayout_login");
        verticalLayout_login->setContentsMargins(40, 40, 40, 40);
        titleLabel_login = new QLabel(loginWidget);
        titleLabel_login->setObjectName("titleLabel_login");
        titleLabel_login->setMinimumSize(QSize(0, 60));
        QFont font;
        font.setFamilies({QString::fromUtf8("Press Start 2P")});
        font.setPointSize(48);
        font.setBold(true);
        titleLabel_login->setFont(font);
        titleLabel_login->setAlignment(Qt::AlignCenter);

        verticalLayout_login->addWidget(titleLabel_login);

        verticalSpacer_login_1 = new QSpacerItem(20, 30, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_login->addItem(verticalSpacer_login_1);

        formWidget = new QWidget(loginWidget);
        formWidget->setObjectName("formWidget");
        formLayout = new QFormLayout(formWidget);
        formLayout->setObjectName("formLayout");
        formLayout->setHorizontalSpacing(15);
        formLayout->setVerticalSpacing(15);
        formLayout->setContentsMargins(20, 20, 20, 20);
        label_username = new QLabel(formWidget);
        label_username->setObjectName("label_username");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label_username);

        usernameInput = new QLineEdit(formWidget);
        usernameInput->setObjectName("usernameInput");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, usernameInput);

        label_password = new QLabel(formWidget);
        label_password->setObjectName("label_password");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label_password);

        passwordInput = new QLineEdit(formWidget);
        passwordInput->setObjectName("passwordInput");
        passwordInput->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, passwordInput);


        verticalLayout_login->addWidget(formWidget);

        verticalSpacer_login_2 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_login->addItem(verticalSpacer_login_2);

        buttonLayout_login = new QHBoxLayout();
        buttonLayout_login->setSpacing(15);
        buttonLayout_login->setObjectName("buttonLayout_login");
        loginButton = new QPushButton(loginWidget);
        loginButton->setObjectName("loginButton");
        loginButton->setMinimumSize(QSize(120, 0));

        buttonLayout_login->addWidget(loginButton);

        signupButton = new QPushButton(loginWidget);
        signupButton->setObjectName("signupButton");
        signupButton->setMinimumSize(QSize(120, 0));

        buttonLayout_login->addWidget(signupButton);


        verticalLayout_login->addLayout(buttonLayout_login);

        verticalSpacer_login_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_login->addItem(verticalSpacer_login_3);

        stackedWidget->addWidget(loginWidget);
        gameWidget = new QWidget();
        gameWidget->setObjectName("gameWidget");
        verticalLayout_game = new QVBoxLayout(gameWidget);
        verticalLayout_game->setObjectName("verticalLayout_game");
        statusLabel = new QLabel(gameWidget);
        statusLabel->setObjectName("statusLabel");
        statusLabel->setMinimumSize(QSize(0, 60));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Press Start 2P")});
        font1.setPointSize(28);
        font1.setBold(true);
        statusLabel->setFont(font1);
        statusLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_game->addWidget(statusLabel);

        difficultyLabel = new QLabel(gameWidget);
        difficultyLabel->setObjectName("difficultyLabel");
        difficultyLabel->setMinimumSize(QSize(0, 40));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Press Start 2P")});
        font2.setPointSize(18);
        font2.setBold(true);
        difficultyLabel->setFont(font2);
        difficultyLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_game->addWidget(difficultyLabel);

        boardWidget = new QWidget(gameWidget);
        boardWidget->setObjectName("boardWidget");
        boardLayout = new QGridLayout(boardWidget);
        boardLayout->setSpacing(10);
        boardLayout->setObjectName("boardLayout");
        boardLayout->setContentsMargins(0, 0, 0, 0);
        boardButtons_0_0 = new QPushButton(boardWidget);
        boardButtons_0_0->setObjectName("boardButtons_0_0");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(boardButtons_0_0->sizePolicy().hasHeightForWidth());
        boardButtons_0_0->setSizePolicy(sizePolicy);
        boardButtons_0_0->setMinimumSize(QSize(120, 120));

        boardLayout->addWidget(boardButtons_0_0, 0, 0, 1, 1);

        boardButtons_0_1 = new QPushButton(boardWidget);
        boardButtons_0_1->setObjectName("boardButtons_0_1");
        sizePolicy.setHeightForWidth(boardButtons_0_1->sizePolicy().hasHeightForWidth());
        boardButtons_0_1->setSizePolicy(sizePolicy);
        boardButtons_0_1->setMinimumSize(QSize(120, 120));

        boardLayout->addWidget(boardButtons_0_1, 0, 1, 1, 1);

        boardButtons_0_2 = new QPushButton(boardWidget);
        boardButtons_0_2->setObjectName("boardButtons_0_2");
        sizePolicy.setHeightForWidth(boardButtons_0_2->sizePolicy().hasHeightForWidth());
        boardButtons_0_2->setSizePolicy(sizePolicy);
        boardButtons_0_2->setMinimumSize(QSize(120, 120));

        boardLayout->addWidget(boardButtons_0_2, 0, 2, 1, 1);

        boardButtons_1_0 = new QPushButton(boardWidget);
        boardButtons_1_0->setObjectName("boardButtons_1_0");
        sizePolicy.setHeightForWidth(boardButtons_1_0->sizePolicy().hasHeightForWidth());
        boardButtons_1_0->setSizePolicy(sizePolicy);
        boardButtons_1_0->setMinimumSize(QSize(120, 120));

        boardLayout->addWidget(boardButtons_1_0, 1, 0, 1, 1);

        boardButtons_1_1 = new QPushButton(boardWidget);
        boardButtons_1_1->setObjectName("boardButtons_1_1");
        sizePolicy.setHeightForWidth(boardButtons_1_1->sizePolicy().hasHeightForWidth());
        boardButtons_1_1->setSizePolicy(sizePolicy);
        boardButtons_1_1->setMinimumSize(QSize(120, 120));

        boardLayout->addWidget(boardButtons_1_1, 1, 1, 1, 1);

        boardButtons_1_2 = new QPushButton(boardWidget);
        boardButtons_1_2->setObjectName("boardButtons_1_2");
        sizePolicy.setHeightForWidth(boardButtons_1_2->sizePolicy().hasHeightForWidth());
        boardButtons_1_2->setSizePolicy(sizePolicy);
        boardButtons_1_2->setMinimumSize(QSize(120, 120));

        boardLayout->addWidget(boardButtons_1_2, 1, 2, 1, 1);

        boardButtons_2_0 = new QPushButton(boardWidget);
        boardButtons_2_0->setObjectName("boardButtons_2_0");
        sizePolicy.setHeightForWidth(boardButtons_2_0->sizePolicy().hasHeightForWidth());
        boardButtons_2_0->setSizePolicy(sizePolicy);
        boardButtons_2_0->setMinimumSize(QSize(120, 120));

        boardLayout->addWidget(boardButtons_2_0, 2, 0, 1, 1);

        boardButtons_2_1 = new QPushButton(boardWidget);
        boardButtons_2_1->setObjectName("boardButtons_2_1");
        sizePolicy.setHeightForWidth(boardButtons_2_1->sizePolicy().hasHeightForWidth());
        boardButtons_2_1->setSizePolicy(sizePolicy);
        boardButtons_2_1->setMinimumSize(QSize(120, 120));

        boardLayout->addWidget(boardButtons_2_1, 2, 1, 1, 1);

        boardButtons_2_2 = new QPushButton(boardWidget);
        boardButtons_2_2->setObjectName("boardButtons_2_2");
        sizePolicy.setHeightForWidth(boardButtons_2_2->sizePolicy().hasHeightForWidth());
        boardButtons_2_2->setSizePolicy(sizePolicy);
        boardButtons_2_2->setMinimumSize(QSize(120, 120));

        boardLayout->addWidget(boardButtons_2_2, 2, 2, 1, 1);


        verticalLayout_game->addWidget(boardWidget);

        gameControlLayout = new QHBoxLayout();
        gameControlLayout->setSpacing(15);
        gameControlLayout->setObjectName("gameControlLayout");
        newGameButtonUI = new QPushButton(gameWidget);
        newGameButtonUI->setObjectName("newGameButtonUI");
        newGameButtonUI->setMinimumSize(QSize(120, 0));

        gameControlLayout->addWidget(newGameButtonUI);

        playAIButtonUI = new QPushButton(gameWidget);
        playAIButtonUI->setObjectName("playAIButtonUI");
        playAIButtonUI->setMinimumSize(QSize(120, 0));

        gameControlLayout->addWidget(playAIButtonUI);

        playHumanButtonUI = new QPushButton(gameWidget);
        playHumanButtonUI->setObjectName("playHumanButtonUI");
        playHumanButtonUI->setMinimumSize(QSize(120, 0));

        gameControlLayout->addWidget(playHumanButtonUI);

        viewHistoryButtonUI = new QPushButton(gameWidget);
        viewHistoryButtonUI->setObjectName("viewHistoryButtonUI");
        viewHistoryButtonUI->setMinimumSize(QSize(120, 0));

        gameControlLayout->addWidget(viewHistoryButtonUI);

        logoutButtonUI = new QPushButton(gameWidget);
        logoutButtonUI->setObjectName("logoutButtonUI");
        logoutButtonUI->setMinimumSize(QSize(120, 0));

        gameControlLayout->addWidget(logoutButtonUI);


        verticalLayout_game->addLayout(gameControlLayout);

        stackedWidget->addWidget(gameWidget);
        historyWidget = new QWidget();
        historyWidget->setObjectName("historyWidget");
        verticalLayout_history = new QVBoxLayout(historyWidget);
        verticalLayout_history->setObjectName("verticalLayout_history");
        verticalLayout_history->setContentsMargins(20, 20, 20, 20);
        titleLabel_history = new QLabel(historyWidget);
        titleLabel_history->setObjectName("titleLabel_history");
        titleLabel_history->setMinimumSize(QSize(0, 60));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Press Start 2P")});
        font3.setPointSize(38);
        font3.setBold(true);
        titleLabel_history->setFont(font3);
        titleLabel_history->setAlignment(Qt::AlignCenter);

        verticalLayout_history->addWidget(titleLabel_history);

        verticalSpacer_history_1 = new QSpacerItem(20, 12, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_history->addItem(verticalSpacer_history_1);

        historyTableView = new QTableView(historyWidget);
        historyTableView->setObjectName("historyTableView");

        verticalLayout_history->addWidget(historyTableView);

        verticalSpacer_history_2 = new QSpacerItem(20, 12, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_history->addItem(verticalSpacer_history_2);

        backButton_history = new QPushButton(historyWidget);
        backButton_history->setObjectName("backButton_history");
        backButton_history->setMinimumSize(QSize(150, 0));

        verticalLayout_history->addWidget(backButton_history);

        stackedWidget->addWidget(historyWidget);

        verticalLayout_main->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 500, 22));
        menuGame = new QMenu(menubar);
        menuGame->setObjectName("menuGame");
        menuView = new QMenu(menubar);
        menuView->setObjectName("menuView");
        menuAccount = new QMenu(menubar);
        menuAccount->setObjectName("menuAccount");
        MainWindow->setMenuBar(menubar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolBar);

        menubar->addAction(menuGame->menuAction());
        menubar->addAction(menuView->menuAction());
        menubar->addAction(menuAccount->menuAction());
        menuGame->addAction(actionNew_Game);
        menuGame->addAction(actionPlay_vs_AI);
        menuGame->addAction(actionPlay_vs_Human);
        menuView->addAction(actionView_History);
        menuAccount->addAction(actionLogout);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Advanced Tic Tac Toe", nullptr));
        actionNew_Game->setText(QCoreApplication::translate("MainWindow", "New Game", nullptr));
        actionView_History->setText(QCoreApplication::translate("MainWindow", "View History", nullptr));
        actionPlay_vs_AI->setText(QCoreApplication::translate("MainWindow", "Play vs AI", nullptr));
        actionPlay_vs_Human->setText(QCoreApplication::translate("MainWindow", "Play vs Human", nullptr));
        actionLogout->setText(QCoreApplication::translate("MainWindow", "Logout", nullptr));
        titleLabel_login->setText(QCoreApplication::translate("MainWindow", "Advanced Tic Tac Toe", nullptr));
        label_username->setText(QCoreApplication::translate("MainWindow", "Username:", nullptr));
        label_password->setText(QCoreApplication::translate("MainWindow", "Password:", nullptr));
        loginButton->setText(QCoreApplication::translate("MainWindow", "Login", nullptr));
        signupButton->setText(QCoreApplication::translate("MainWindow", "Sign Up", nullptr));
        statusLabel->setText(QCoreApplication::translate("MainWindow", "Player X's turn", nullptr));
        difficultyLabel->setText(QString());
        boardButtons_0_0->setText(QString());
        boardButtons_0_1->setText(QString());
        boardButtons_0_2->setText(QString());
        boardButtons_1_0->setText(QString());
        boardButtons_1_1->setText(QString());
        boardButtons_1_2->setText(QString());
        boardButtons_2_0->setText(QString());
        boardButtons_2_1->setText(QString());
        boardButtons_2_2->setText(QString());
        newGameButtonUI->setText(QCoreApplication::translate("MainWindow", "New Game", nullptr));
        playAIButtonUI->setText(QCoreApplication::translate("MainWindow", "Play vs AI", nullptr));
        playHumanButtonUI->setText(QCoreApplication::translate("MainWindow", "Play vs Human", nullptr));
        viewHistoryButtonUI->setText(QCoreApplication::translate("MainWindow", "View History", nullptr));
        logoutButtonUI->setText(QCoreApplication::translate("MainWindow", "Logout", nullptr));
        titleLabel_history->setText(QCoreApplication::translate("MainWindow", "Game History", nullptr));
        backButton_history->setText(QCoreApplication::translate("MainWindow", "Back to Game", nullptr));
        menuGame->setTitle(QCoreApplication::translate("MainWindow", "Game", nullptr));
        menuView->setTitle(QCoreApplication::translate("MainWindow", "View", nullptr));
        menuAccount->setTitle(QCoreApplication::translate("MainWindow", "Account", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
