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
    appcontroller.cpp

HEADERS  += gameswindow.h \
    logindialog.h \
    itchioapi.h \
    appcontroller.h

FORMS    += gameswindow.ui \
    logindialog.ui
