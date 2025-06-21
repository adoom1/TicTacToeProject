QT += core gui widgets testlib
CONFIG += c++11 console
CONFIG -= app_bundle

# This is crucial for standalone executable
TARGET = AdvancedTicTacToeTests
TEMPLATE = app

# Include paths
INCLUDEPATH += ../
INCLUDEPATH += D:/sqlite
INCLUDEPATH += "C:/msys64/mingw64/include"

# Source files from main project
SOURCES += \
    ../BoardStateDelegate.cpp \
    ../DBManager.cpp \
    ../Game.cpp \
    ../GameHistoryModel.cpp \
    ../User.cpp \
    ../difficultyselector.cpp \
    ../mainwindow.cpp \
    ../playerchoicedialog.cpp \
    D:/sqlite/sqlite3.c \
    test_game.cpp \
    test_user.cpp \
    test_dbmanager.cpp \
    test_gamehistory.cpp \
    test_performance.cpp \
    main_test.cpp

# Header files
HEADERS += \
    ../BoardStateDelegate.h \
    ../DBManager.h \
    ../Game.h \
    ../GameHistoryModel.h \
    ../User.h \
    ../difficultyselector.h \
    ../mainwindow.h \
    ../playerchoicedialog.h \
    test_game.h \
    test_user.h \
    test_dbmanager.h \
    test_gamehistory.h \
    test_performance.h

# UI files
FORMS += \
    ../mainwindow.ui \
    ../difficultyselector.ui \
    ../playerchoicedialog.ui

# Libraries
LIBS += -L"C:/msys64/mingw64/lib" -lssl -lcrypto -lws2_32 -lgdi32 -lcrypt32
