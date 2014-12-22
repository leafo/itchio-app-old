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
    appWindow->showMinimized();

    appWindow->setWindowFlags(appWindow->windowFlags() ^ Qt::Tool);
}

void AppController::show()
{
    appWindow->setWindowFlags(appWindow->windowFlags() ^ Qt::Tool);

    appWindow->show();
    appWindow->setWindowState((appWindow->windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
}

void AppController::quit()
{
    QCoreApplication::exit();
}

void AppController::trayIconDoubleClick(QSystemTrayIcon::ActivationReason reason)
{
    if(reason == QSystemTrayIcon::DoubleClick
            && !appWindow->isVisible())
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

    appWindow->show();
}
