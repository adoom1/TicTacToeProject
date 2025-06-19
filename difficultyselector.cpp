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

    // The items for difficultyComboBox are now defined directly in difficultyselector.ui.
    // REMOVED: ui->difficultyComboBox->addItem("Easy", static_cast<int>(AIDifficulty::EASY));
    // REMOVED: ui->difficultyComboBox->addItem("Medium", static_cast<int>(AIDifficulty::MEDIUM));
    // REMOVED: ui->difficultyComboBox->addItem("Hard", static_cast<int>(AIDifficulty::HARD));
    // REMOVED: ui->difficultyComboBox->addItem("Impossible", static_cast<int>(AIDifficulty::IMPOSSIBLE));

    // The QComboBox in the UI file defaults the 'Easy' item to index 0,
    // 'Medium' to 1, 'Hard' to 2, 'Impossible' to 3.
    // Ensure the data stored with each item in the UI matches the AIDifficulty enum values.
    // Qt Designer typically stores the text as the item data by default unless explicitly set.
    // Since our C++ relies on currentData().toInt() mapping to AIDifficulty enum values,
    // we need to make sure the data values match the enum order (0, 1, 2, 3).
    // If they were not explicitly set in the UI designer (e.g., in "User Role" property),
    // they might default to something else.
    // Assuming 'Easy' is index 0, 'Medium' 1, etc., then this is implicitly correct.

    // Connections are already defined in the .ui file's <connections> section
    // for Ok/Cancel buttons.
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
