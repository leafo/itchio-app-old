#-------------------------------------------------
#
# Project created by QtCreator 2014-09-21T19:24:58
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = itchio
TEMPLATE = app


SOURCES += main.cpp\
        gameswindow.cpp \
    logindialog.cpp \
    itchioapi.cpp \
    appcontroller.cpp \
    objects/game.cpp \
    gamerow.cpp

HEADERS  += gameswindow.h \
    logindialog.h \
    itchioapi.h \
    appcontroller.h \
    objects/game.h \
    gamerow.h

FORMS    += gameswindow.ui \
    logindialog.ui

RESOURCES += \
    resources.qrc

LIBS += `pkg-config --libs openssl`

DISTFILES += \
    stylesheet.qss
