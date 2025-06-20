QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

QMAKE_CXXFLAGS += -Wno-unused -Wno-unused-but-set-variable -Wno-unused-parameter

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

HEADERS += \
    BoardStateDelegate.h \
    DBManager.h \
    Game.h \
    GameHistoryModel.h \
    User.h \
    difficultyselector.h \
    mainwindow.h \
    playerchoicedialog.h

FORMS += \
    mainwindow.ui \
    difficultyselector.ui \
    playerchoicedialog.ui

# Use SQLite system library
LIBS += -lsqlite3

# Platform-specific libraries
win32 {
    INCLUDEPATH += D:/sqlite
    INCLUDEPATH += C:/msys64/mingw64/include
    LIBS += -L"C:/msys64/mingw64/lib" -lcrypto
    LIBS += -lgdi32 -lws2_32 -lcrypt32 -lmsvcrt
}

# Resource file (Windows icons)
RC_FILE = appicon.rc
DISTFILES += appicon.rc

# Installation path
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
