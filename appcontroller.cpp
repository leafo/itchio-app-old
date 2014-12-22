#include <QDebug>
#include "appcontroller.h"
#include "appwindow.h"
#include "logindialog.h"
#include "gameswindow.h"

AppController::AppController(QObject *parent) :
    QObject(parent)
{
    api = new ItchioApi(this);

    showWindowMain();
    showTrayIcon();
}

void AppController::hide()
{
    activeWindow->showMinimized();

    activeWindow->setWindowFlags(activeWindow->windowFlags() ^ Qt::Tool);
}

void AppController::show()
{
    activeWindow->setWindowFlags(activeWindow->windowFlags() ^ Qt::Tool);

    QApplication::setActiveWindow(activeWindow);
    activeWindow->show();
    activeWindow->setWindowState(activeWindow->windowState() & (~Qt::WindowMinimized | Qt::WindowActive));
}

void AppController::quit()
{
    QCoreApplication::exit();
}

void AppController::trayIconDoubleClick(QSystemTrayIcon::ActivationReason reason)
{
    if(reason == QSystemTrayIcon::DoubleClick
            && !activeWindow->isVisible())
    {
        show();
    }
}

void AppController::showTrayIcon()
{
    trayIcon = new QSystemTrayIcon(this);
    trayIconMenu = new QMenu();

    actionQuit = new QAction("Quit", this);

    connect (actionQuit, SIGNAL(triggered()), this, SLOT(quit()));
    connect (trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
             this, SLOT(trayIconDoubleClick(QSystemTrayIcon::ActivationReason)));

    trayIconMenu->addAction (actionQuit);

    trayIcon->setIcon(QIcon(":/images/images/itchio-icon-16.png"));
    trayIcon->setContextMenu (trayIconMenu);
    trayIcon->show();
}

void AppController::showTrayIconNotification(TrayNotifications notification, int duration)
{
    if(trayIcon->supportsMessages()) {
        switch(notification) {
        case NOTIFICATION_TEST:
            trayIcon->showMessage("Title", "Test", QSystemTrayIcon::Information, duration);
            break;
        }
    }
}

void AppController::showWindowMain()
{
    appWindow = new AppWindow(this);
    appWindow->setWindowIcon(QIcon(":/images/images/itchio-icon-200.png"));

    activeWindow = appWindow;
    appWindow->show();
}

void AppController::showLogin()
{
    loginDialog = new LoginDialog(this);
    activeWindow = loginDialog;
    loginDialog->show();
}

void AppController::showGames()
{
    loginDialog->hide();

    gamesWindow = new GamesWindow(this);
    activeWindow = gamesWindow;
    gamesWindow->show();
}
