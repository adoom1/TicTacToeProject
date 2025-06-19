// playerchoicedialog.cpp
#include "playerchoicedialog.h"
#include <QHBoxLayout> // Include for QHBoxLayout
#include <QLabel>      // Include for QLabel
#include <QPushButton> // Include for QPushButton
#include <QVBoxLayout> // Include for QVBoxLayout

PlayerChoiceDialog::PlayerChoiceDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PlayerChoiceDialog())
    ,                   // Initialize the ui object
    selectedPlayer(' ') // Initialize
{
    ui->setupUi(this);      // Set up the UI from the .ui file for this dialog
    setModal(true);         // Ensure it's a modal dialog
    setFixedSize(300, 200); // Fixed size for the dialog

    // Apply main dialog stylesheet. Styles for specific buttons (xButton, oButton)
    // and label (label_playAs) are already defined within playerchoicedialog.ui directly.
    setStyleSheet(
        "QDialog { background-color: #1a1a1a; border: 2px solid #00ff00; border-radius: 10px; }");

    // The on_xButton_clicked and on_oButton_clicked slots are usually
    // automatically connected by Qt's auto-connection feature if they follow
    // the naming convention. However, explicitly connecting them here is safer
    // if auto-connection might be disabled or problematic for any reason.
    connect(ui->xButton, &QPushButton::clicked, this, &PlayerChoiceDialog::on_xButton_clicked);
    connect(ui->oButton, &QPushButton::clicked, this, &PlayerChoiceDialog::on_oButton_clicked);
}

PlayerChoiceDialog::~PlayerChoiceDialog()
{
    delete ui; // Clean up the ui object
}

char PlayerChoiceDialog::getSelectedPlayer() const
{
    return selectedPlayer;
}

void PlayerChoiceDialog::on_xButton_clicked()
{
    selectedPlayer = 'X';
    accept(); // Close dialog with Accepted result
}

void PlayerChoiceDialog::on_oButton_clicked()
{
    selectedPlayer = 'O';
    accept(); // Close dialog with Accepted result
}
