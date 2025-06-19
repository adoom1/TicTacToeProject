// difficultyselector.h
#ifndef DIFFICULTYSELECTOR_H
#define DIFFICULTYSELECTOR_H

#include <QDialog>
#include <QComboBox> // Required for AIDifficulty enum if it was previously in MainWindow
#include "Game.h"    // Include Game.h to access AIDifficulty enum
#include "ui_difficultyselector.h" // Include the generated UI header for this dialog

namespace Ui {
class DifficultyDialog; // Forward declaration for the Ui namespace
}

class DifficultyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DifficultyDialog(QWidget *parent = nullptr);
    ~DifficultyDialog();

    AIDifficulty getSelectedDifficulty() const;

private:
    Ui::DifficultyDialog *ui; // Pointer to the generated UI for this dialog
};

#endif // DIFFICULTYSELECTOR_H
