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
    itchioapi.cpp \
    appcontroller.cpp \
    appwindow.cpp \
    gameswindow.cpp \
    logindialog.cpp \
    objects/game.cpp \
    gamerow.cpp

HEADERS  += itchioapi.h \
    appcontroller.h \
    appwindow.h \
    gameswindow.h \
    logindialog.h \
    objects/game.h \
    gamerow.h

FORMS    += appwindow.ui \
    gameswindow.ui \
    logindialog.ui


RESOURCES += \
    resources.qrc

# CONFIG += link_pkgconfig
# PKGCONFIG += openssl
