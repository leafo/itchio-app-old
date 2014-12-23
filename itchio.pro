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
    appwindow.cpp \
    gameswindow.cpp \
    objects/game.cpp \
    gamerow.cpp \
    widgets/loginwidget.cpp

HEADERS  += itchioapi.h \
    appcontroller.h \
    appwindow.h \
    gameswindow.h \
    objects/game.h \
    gamerow.h \
    widgets/loginwidget.h

FORMS    += appwindow.ui \
    gameswindow.ui \
    widgets/loginwidget.ui


RESOURCES += \
    resources.qrc \

CONFIG += link_pkgconfig

unix:PKGCONFIG += openssl

win32:LIBS += -LC:/OpenSSL-Win32/lib -lubsec
win32:INCLUDEPATH += C:/OpenSSL-Win32/include
