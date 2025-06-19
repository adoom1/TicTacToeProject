/********************************************************************************
** Form generated from reading UI file 'playerchoicedialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYERCHOICEDIALOG_H
#define UI_PLAYERCHOICEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_PlayerChoiceDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label_playAs;
    QHBoxLayout *horizontalLayout;
    QPushButton *xButton;
    QPushButton *oButton;

    void setupUi(QDialog *PlayerChoiceDialog)
    {
        if (PlayerChoiceDialog->objectName().isEmpty())
            PlayerChoiceDialog->setObjectName("PlayerChoiceDialog");
        PlayerChoiceDialog->resize(300, 200);
        verticalLayout = new QVBoxLayout(PlayerChoiceDialog);
        verticalLayout->setSpacing(20);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(20, 20, 20, 20);
        label_playAs = new QLabel(PlayerChoiceDialog);
        label_playAs->setObjectName("label_playAs");
        QFont font;
        font.setFamilies({QString::fromUtf8("Press Start 2P")});
        font.setPointSize(18);
        label_playAs->setFont(font);
        label_playAs->setStyleSheet(QString::fromUtf8("color: #00ffff; text-shadow: 0 0 5px #00ffff;"));
        label_playAs->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_playAs);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(20);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setAlignment(Qt::AlignCenter);
        xButton = new QPushButton(PlayerChoiceDialog);
        xButton->setObjectName("xButton");
        xButton->setMinimumSize(QSize(100, 100));
        xButton->setMaximumSize(QSize(100, 100));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Press Start 2P")});
        font1.setPointSize(40);
        font1.setBold(true);
        xButton->setFont(font1);
        xButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	font-size: 40px; color: #00ffff; border: 4px solid #00ffff;\n"
"	background-color: #8a2be2; border-radius: 8px; \n"
"	font-family: 'Press Start 2P', monospace; font-weight: bold;\n"
"	text-align: center;\n"
"}\n"
"QPushButton:hover { background-color: #6a0dad; }\n"
"QPushButton:pressed { background-color: #4b0082; }"));

        horizontalLayout->addWidget(xButton);

        oButton = new QPushButton(PlayerChoiceDialog);
        oButton->setObjectName("oButton");
        oButton->setMinimumSize(QSize(100, 100));
        oButton->setMaximumSize(QSize(100, 100));
        oButton->setFont(font1);
        oButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	font-size: 40px; color: #ff00ff; border: 4px solid #ff00ff;\n"
"	background-color: #8a2be2; border-radius: 8px; \n"
"	font-family: 'Press Start 2P', monospace; font-weight: bold;\n"
"	text-align: center;\n"
"}\n"
"QPushButton:hover { background-color: #6a0dad; }\n"
"QPushButton:pressed { background-color: #4b0082; }"));

        horizontalLayout->addWidget(oButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(PlayerChoiceDialog);

        QMetaObject::connectSlotsByName(PlayerChoiceDialog);
    } // setupUi

    void retranslateUi(QDialog *PlayerChoiceDialog)
    {
        PlayerChoiceDialog->setWindowTitle(QCoreApplication::translate("PlayerChoiceDialog", "Choose Your Mark", nullptr));
        label_playAs->setText(QCoreApplication::translate("PlayerChoiceDialog", "Play as:", nullptr));
        xButton->setText(QCoreApplication::translate("PlayerChoiceDialog", "X", nullptr));
        oButton->setText(QCoreApplication::translate("PlayerChoiceDialog", "O", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PlayerChoiceDialog: public Ui_PlayerChoiceDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYERCHOICEDIALOG_H
