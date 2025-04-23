#include <QApplication>
#include <QWidget>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QIcon appIcon(":/icons/tictactoe_icon.png"); // Add an icon to your resource file
    app.setWindowIcon(appIcon);

    MainWindow mainWindow;
    mainWindow.setWindowTitle("Advanced Tic Tac Toe");
    mainWindow.show();

    return app.exec();
}
