# Qt Modules
QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# C++11 support
CONFIG += c++11

# Compiler flags and deprecation settings
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000
QMAKE_CXXFLAGS += -Wno-unused -Wno-unused-but-set-variable -Wno-unused-parameter

# Set output binary name
TARGET = TicTacToe1

# Set output directory (e.g., ./release/TicTacToe1)
DESTDIR = release

# Source files
SOURCES += \
    BoardStateDelegate.cpp \
    DBManager.cpp \
    Game.cpp \
    GameHistoryModel.cpp \
    User.cpp \
    difficultyselector.cpp \
    main.cpp \
    mainwindow.cpp \
    playerchoicedialog.cpp

# Header files
HEADERS += \
    BoardStateDelegate.h \
    DBManager.h \
    Game.h \
    GameHistoryModel.h \
    User.h \
    difficultyselector.h \
    mainwindow.h \
    playerchoicedialog.h

# UI files
FORMS += \
    mainwindow.ui \
    difficultyselector.ui \
    playerchoicedialog.ui

# Required system libraries
LIBS += -lsqlite3 -lcrypto

# Windows-only libraries and paths
win32 {
    INCLUDEPATH += C:/msys64/mingw64/include
    LIBS += -L"C:/msys64/mingw64/lib"
    LIBS += -lgdi32 -lws2_32 -lcrypt32 -lmsvcrt
}

# Windows application icon
RC_FILE = appicon.rc
DISTFILES += appicon.rc

# Optional installation directory
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
