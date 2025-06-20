/********************************************************************************
** Form generated from reading UI file 'difficultyselector.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIFFICULTYSELECTOR_H
#define UI_DIFFICULTYSELECTOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DifficultyDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label_difficulty;
    QComboBox *difficultyComboBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DifficultyDialog)
    {
        if (DifficultyDialog->objectName().isEmpty())
            DifficultyDialog->setObjectName("DifficultyDialog");
        DifficultyDialog->resize(350, 200);
        verticalLayout = new QVBoxLayout(DifficultyDialog);
        verticalLayout->setSpacing(15);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(20, 20, 20, 20);
        label_difficulty = new QLabel(DifficultyDialog);
        label_difficulty->setObjectName("label_difficulty");
        QFont font;
        font.setFamilies({QString::fromUtf8("Press Start 2P")});
        font.setPointSize(18);
        label_difficulty->setFont(font);
        label_difficulty->setStyleSheet(QString::fromUtf8("color: #00ffff; padding: 5px; text-shadow: 0 0 5px #00ffff;"));

        verticalLayout->addWidget(label_difficulty);

        difficultyComboBox = new QComboBox(DifficultyDialog);
        QIcon icon;
        icon.addFile(QString::fromUtf8(""), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        difficultyComboBox->addItem(icon, QString());
        difficultyComboBox->addItem(QString());
        difficultyComboBox->addItem(QString());
        difficultyComboBox->addItem(QString());
        difficultyComboBox->setObjectName("difficultyComboBox");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Press Start 2P")});
        font1.setPointSize(16);
        difficultyComboBox->setFont(font1);
        difficultyComboBox->setStyleSheet(QString::fromUtf8("QComboBox { \n"
"	font-family: 'Press Start 2P', monospace; font-size: 16px; padding: 8px; border: 2px solid #ff00ff; \n"
"	border-radius: 5px; background-color: #333333; color: #00ff00; selection-background-color: #8a2be2; min-width: 200px; \n"
"	text-shadow: 0 0 3px #00ff00; \n"
"}\n"
"QComboBox::drop-down { border: 0px; }\n"
"QComboBox::down-arrow { image: url(:/icons/arrow_down.png); }"));

        verticalLayout->addWidget(difficultyComboBox);

        buttonBox = new QDialogButtonBox(DifficultyDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(DifficultyDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, DifficultyDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, DifficultyDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(DifficultyDialog);
    } // setupUi

    void retranslateUi(QDialog *DifficultyDialog)
    {
        DifficultyDialog->setWindowTitle(QCoreApplication::translate("DifficultyDialog", "Select AI Difficulty", nullptr));
        label_difficulty->setText(QCoreApplication::translate("DifficultyDialog", "Select AI Difficulty Level:", nullptr));
        difficultyComboBox->setItemText(0, QCoreApplication::translate("DifficultyDialog", "Easy", nullptr));
        difficultyComboBox->setItemText(1, QCoreApplication::translate("DifficultyDialog", "Medium", nullptr));
        difficultyComboBox->setItemText(2, QCoreApplication::translate("DifficultyDialog", "Hard", nullptr));
        difficultyComboBox->setItemText(3, QCoreApplication::translate("DifficultyDialog", "Impossible", nullptr));

    } // retranslateUi

};

namespace Ui {
    class DifficultyDialog: public Ui_DifficultyDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIFFICULTYSELECTOR_H
