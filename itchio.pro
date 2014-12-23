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
    widgets/loginwidget.cpp \
	widgets/librarywidget.cpp \
    objects/game.cpp \
    gamerow.cpp \
    objects/user.cpp \
    objects/downloadkey.cpp


HEADERS += itchioapi.h \
	traynotifications.h \
    appcontroller.h \
	appsettings.h \
    appwindow.h \
    widgets/loginwidget.h \
	widgets/librarywidget.h \
    objects/game.h \
	gamerow.h \
    objects/user.h \
    objects/downloadkey.h


FORMS += appwindow.ui \
    widgets/loginwidget.ui \
    widgets/librarywidget.ui


RESOURCES += \
    resources.qrc \

CONFIG += link_pkgconfig

unix:PKGCONFIG += openssl

win32:LIBS += -LC:/OpenSSL-Win32/lib -lubsec
win32:INCLUDEPATH += C:/OpenSSL-Win32/include
