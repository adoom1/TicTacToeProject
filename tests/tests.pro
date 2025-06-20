QT += core gui widgets testlib \
    quick
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 console
CONFIG -= app_bundle

TARGET = AdvancedTicTacToeTests
TEMPLATE = app

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000
QMAKE_CXXFLAGS += -Wno-unused -Wno-unused-but-set-variable -Wno-unused-parameter

# Include paths for your main project source files
INCLUDEPATH += ../
INCLUDEPATH += C:/sqlite
INCLUDEPATH += "C:/msys64/mingw64/include"
INCLUDEPATH += $$PWD/..
# Source files from your main project
SOURCES += \
    ../BoardStateDelegate.cpp \
    ../DBManager.cpp \
    ../Game.cpp \
    ../GameHistoryModel.cpp \
    ../User.cpp \
    ../difficultyselector.cpp \
    ../mainwindow.cpp \
    ../playerchoicedialog.cpp \
    C:/sqlite/sqlite3.c \
    main.cpp \
    test_dbmanager.cpp \
    test_game.cpp \
    test_gamehistory.cpp \
    test_user.cpp

# Header files from your main project
HEADERS += \
    ../BoardStateDelegate.h \
    ../DBManager.h \
    ../Game.h \
    ../GameHistoryModel.h \
    ../User.h \
    ../difficultyselector.h \
    ../mainwindow.h \
    ../playerchoicedialog.h \
    ../test_user.h \
    ../test_dbmanager.h \
    ../test_gamehistorymodel.h \
    test_dbmanager.h \
    test_game.h \
    test_gamehistory.h \
    test_user.h

# UI files from your main project
FORMS += \
    ../mainwindow.ui \
    ../difficultyselector.ui \
    ../playerchoicedialog.ui

# Libraries
LIBS += -L"C:/msys64/mingw64/lib" -lssl -lcrypto -lws2_32 -lgdi32 -lcrypt32
LIBS += -ladvapi32
