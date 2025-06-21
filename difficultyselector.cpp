// difficultyselector.cpp
#include "difficultyselector.h"
#include <QLabel> // Required for QLabel
#include <QComboBox> // Required for QComboBox
#include <QDialogButtonBox> // Required for QDialogButtonBox
#include <QVBoxLayout> // Required for QVBoxLayout

DifficultyDialog::DifficultyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DifficultyDialog()) // Initialize the ui object
{
    ui->setupUi(this); // Set up the UI from the .ui file for this dialog

    setWindowTitle("Select AI Difficulty"); // Set window title
    setModal(true); // Make it a modal dialog

    // Set stylesheet for the dialog itself. Styles for inner widgets are in the .ui file.
    setStyleSheet(
        "QDialog { background-color: #1a1a1a; border: 2px solid #00ff00; border-radius: 10px; }"
        );

}

DifficultyDialog::~DifficultyDialog()
{
    delete ui; // Clean up the ui object
}

AIDifficulty DifficultyDialog::getSelectedDifficulty() const
{
    // Retrieve the selected difficulty using the index, which corresponds to the enum values
    // if the items were added in the correct order in the UI file.
    int currentIndex = ui->difficultyComboBox->currentIndex();
    return static_cast<AIDifficulty>(currentIndex);
}
