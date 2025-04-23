QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

QMAKE_CXXFLAGS += -Wno-unused -Wno-unused-but-set-variable -Wno-unused-parameter

SOURCES += \
    DBManager.cpp \
    Game.cpp \
    GameHistoryModel.cpp \
    User.cpp \
    main.cpp \
    mainwindow.cpp \
    D:/sqlite/sqlite3.c

HEADERS += \
    DBManager.h \
    Game.h \
    GameHistoryModel.h \
    User.h \
    mainwindow.h

INCLUDEPATH += D:/sqlite
INCLUDEPATH += C:/msys64/mingw64/include

LIBS += -L"C:/msys64/mingw64/lib" -lcrypto
LIBS += -lgdi32 -lws2_32 -lcrypt32 -lmsvcrt

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
