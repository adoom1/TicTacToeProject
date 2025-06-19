// playerchoicedialog.h
#ifndef PLAYERCHOICEDIALOG_H
#define PLAYERCHOICEDIALOG_H

#include <QDialog>
#include "ui_playerchoicedialog.h" // Include the generated UI header for this dialog

// Forward declaration for the Ui namespace
namespace Ui {
class PlayerChoiceDialog;
}

class PlayerChoiceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlayerChoiceDialog(QWidget *parent = nullptr);
    ~PlayerChoiceDialog();

    char getSelectedPlayer() const;

private slots:
    // These slots are automatically connected by Qt's naming convention (on_objectName_signalName)
    // if setupUi is called and the objectName exists in the .ui file.
    void on_xButton_clicked();
    void on_oButton_clicked();

private:
    Ui::PlayerChoiceDialog *ui; // Pointer to the generated UI class for this dialog
    char selectedPlayer;
};

#endif // PLAYERCHOICEDIALOG_H
