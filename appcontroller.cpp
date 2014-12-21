#include <QDebug>
#include "appcontroller.h"
#include "gameswindow.h"
#include "logindialog.h"

AppController::AppController(QObject *parent) :
    QObject(parent)
{
    api = new ItchioApi(this);

    showLogin();
    showTrayIcon();
}

void AppController::hide() {
    activeWindow->showMinimized();

    activeWindow->setWindowFlags(activeWindow->windowFlags() ^ QFlag(8));
}

void AppController::show() {
    activeWindow->setWindowFlags(activeWindow->windowFlags() ^ QFlag(8));

    QApplication::setActiveWindow(activeWindow);
    activeWindow->show();
    activeWindow->setWindowState(Qt::WindowActive);
}

void AppController::quit() {
    QCoreApplication::exit();
}

void AppController::trayIconDoubleLeftClick(QSystemTrayIcon::ActivationReason reason){
    if(reason == QSystemTrayIcon::DoubleClick
            && !activeWindow->isVisible()) show();
}

void AppController::showTrayIcon() {
    trayIcon = new QSystemTrayIcon(this);
    trayIconMenu = new QMenu();

    actionQuit = new QAction("Quit", this);

    connect (actionQuit, SIGNAL(triggered()), this, SLOT(quit()));
    connect (trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
             this, SLOT(trayIconDoubleLeftClick(QSystemTrayIcon::ActivationReason)));

    trayIconMenu->addAction (actionQuit);

    trayIcon->setIcon(QIcon(":/images/images/itchio-icon-16.png"));
    trayIcon->setContextMenu (trayIconMenu);
    trayIcon->show();
}



void AppController::showLogin() {
    loginDialog = new LoginDialog(this);
    activeWindow = loginDialog;
    loginDialog->show();
}

void AppController::showGames() {
    loginDialog->hide();

    gamesWindow = new GamesWindow(this);
    activeWindow = gamesWindow;
    gamesWindow->show();
}
