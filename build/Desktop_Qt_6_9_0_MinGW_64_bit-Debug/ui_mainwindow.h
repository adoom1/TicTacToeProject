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
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout;
    QPushButton *button_2_2;
    QPushButton *button_0_0;
    QPushButton *button_0_2;
    QPushButton *button_1_0;
    QPushButton *button_2_1;
    QPushButton *button_1_1;
    QPushButton *button_0_1;
    QPushButton *button_1_2;
    QPushButton *button_2_0;
    QLabel *statuslabel;
    QHBoxLayout *horizontalLayout;
    QLabel *scoreXLabel;
    QLabel *scoreOLabel;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *newGameButton;
    QPushButton *resetScoreButton;
    QPushButton *showHistoryButton;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->setEnabled(false);
        MainWindow->resize(517, 500);
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        MainWindow->setFont(font);
        MainWindow->setToolTipDuration(-1);
        MainWindow->setIconSize(QSize(400, 500));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName("gridLayout_2");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(5);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(5, 5, 5, 5);
        button_2_2 = new QPushButton(centralwidget);
        button_2_2->setObjectName("button_2_2");
        button_2_2->setMinimumSize(QSize(80, 80));

        gridLayout->addWidget(button_2_2, 2, 2, 1, 1);

        button_0_0 = new QPushButton(centralwidget);
        button_0_0->setObjectName("button_0_0");
        button_0_0->setMinimumSize(QSize(80, 80));

        gridLayout->addWidget(button_0_0, 0, 0, 1, 1);

        button_0_2 = new QPushButton(centralwidget);
        button_0_2->setObjectName("button_0_2");
        button_0_2->setMinimumSize(QSize(80, 80));

        gridLayout->addWidget(button_0_2, 0, 2, 1, 1);

        button_1_0 = new QPushButton(centralwidget);
        button_1_0->setObjectName("button_1_0");
        button_1_0->setMinimumSize(QSize(80, 80));

        gridLayout->addWidget(button_1_0, 1, 0, 1, 1);

        button_2_1 = new QPushButton(centralwidget);
        button_2_1->setObjectName("button_2_1");
        button_2_1->setMinimumSize(QSize(80, 80));

        gridLayout->addWidget(button_2_1, 2, 1, 1, 1);

        button_1_1 = new QPushButton(centralwidget);
        button_1_1->setObjectName("button_1_1");
        button_1_1->setMinimumSize(QSize(80, 80));

        gridLayout->addWidget(button_1_1, 1, 1, 1, 1);

        button_0_1 = new QPushButton(centralwidget);
        button_0_1->setObjectName("button_0_1");
        button_0_1->setMinimumSize(QSize(80, 80));

        gridLayout->addWidget(button_0_1, 0, 1, 1, 1);

        button_1_2 = new QPushButton(centralwidget);
        button_1_2->setObjectName("button_1_2");
        button_1_2->setMinimumSize(QSize(80, 80));

        gridLayout->addWidget(button_1_2, 1, 2, 1, 1);

        button_2_0 = new QPushButton(centralwidget);
        button_2_0->setObjectName("button_2_0");
        button_2_0->setMinimumSize(QSize(80, 80));

        gridLayout->addWidget(button_2_0, 2, 0, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        statuslabel = new QLabel(centralwidget);
        statuslabel->setObjectName("statuslabel");
        statuslabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(statuslabel);


        gridLayout_2->addLayout(verticalLayout_2, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        scoreXLabel = new QLabel(centralwidget);
        scoreXLabel->setObjectName("scoreXLabel");

        horizontalLayout->addWidget(scoreXLabel);

        scoreOLabel = new QLabel(centralwidget);
        scoreOLabel->setObjectName("scoreOLabel");

        horizontalLayout->addWidget(scoreOLabel);


        gridLayout_2->addLayout(horizontalLayout, 2, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        newGameButton = new QPushButton(centralwidget);
        newGameButton->setObjectName("newGameButton");

        horizontalLayout_2->addWidget(newGameButton);

        resetScoreButton = new QPushButton(centralwidget);
        resetScoreButton->setObjectName("resetScoreButton");

        horizontalLayout_2->addWidget(resetScoreButton);

        showHistoryButton = new QPushButton(centralwidget);
        showHistoryButton->setObjectName("showHistoryButton");

        horizontalLayout_2->addWidget(showHistoryButton);


        gridLayout_2->addLayout(horizontalLayout_2, 3, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        button_2_2->setText(QString());
        button_0_0->setText(QString());
        button_0_2->setText(QString());
        button_1_0->setText(QString());
        button_2_1->setText(QString());
        button_1_1->setText(QString());
        button_0_1->setText(QString());
        button_1_2->setText(QString());
        button_2_0->setText(QString());
        statuslabel->setText(QCoreApplication::translate("MainWindow", "Game Status: Player X's Turn", nullptr));
        scoreXLabel->setText(QCoreApplication::translate("MainWindow", "Player X: 0", nullptr));
        scoreOLabel->setText(QCoreApplication::translate("MainWindow", "Player O: 0", nullptr));
        newGameButton->setText(QCoreApplication::translate("MainWindow", "New Game", nullptr));
        resetScoreButton->setText(QCoreApplication::translate("MainWindow", "Reset Score", nullptr));
        showHistoryButton->setText(QCoreApplication::translate("MainWindow", "Show History", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
