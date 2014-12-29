#-------------------------------------------------
#
# Project created by QtCreator 2014-09-21T19:24:58
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = itchio
TEMPLATE = app


SOURCES += main.cpp \
    itchioapi.cpp \
    appcontroller.cpp \
    appsettings.cpp \
    appwindow.cpp \
    secondarywindow.cpp \
    widgets/librarywidget.cpp \
    widgets/secondary/loginwidget.cpp \
    widgets/secondary/settingswidget.cpp \
    objects/game.cpp \
    gamerow.cpp \
    objects/user.cpp \
    objects/downloadkey.cpp \
    objects/upload.cpp


HEADERS += itchioapi.h \
    traynotifications.h \
    appcontroller.h \
    appsettings.h \
    appwindow.h \
    secondarywindow.h \
    widgets/librarywidget.h \
    widgets/secondary/loginwidget.h \
    widgets/secondary/settingswidget.h \
    objects/game.h \
    gamerow.h \
    objects/user.h \
    objects/downloadkey.h \
    objects/upload.h


FORMS += appwindow.ui \
    secondarywindow.ui \
    widgets/librarywidget.ui \
    widgets/secondary/loginwidget.ui \
    widgets/secondary/settingswidget.ui

RESOURCES += \
    resources.qrc \

include(itchio.pri)
