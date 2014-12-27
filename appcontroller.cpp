#include <QDebug>
#include "appcontroller.h"
#include "appwindow.h"
#include "secondarywindow.h"
#include "widgets/loginwidget.h"
#include "widgets/librarywidget.h"
#include "widgets/secondary/settingswidget.h"

using itchio::AppController;

//TODO: Create custom maximizing pipeline to better handle taskbars.

AppController::AppController(int& argc, char** argv) :
    QApplication(argc, argv),
    settings_("itchio.ini"),
    api_(settings_.apiUrl()),
    actionQuit(nullptr),
    actionSettings(nullptr),
    appWindow_(*this),
    settingsWindow_(appWindow_),
    trayIcon(nullptr),
    trayIconMenu(nullptr)
{
    if (settings_.autoLogin() && settings_.hasValidApiKey()) {
        api_.loginWithApiKey(settings_.apiKey());
    }
    showTrayIcon();
    showAppWindow();
}

void AppController::hide()
{
    qDebug() << "hide" << appWindow_.pos();
    if (!appWindow_.oldPosition.isNull()) {
        appWindow_.move(appWindow_.oldPosition);
    }

    appWindow_.showMinimized();

    appWindow_.setWindowFlags(appWindow_.windowFlags() ^ Qt::Tool);
}

void AppController::show()
{
    qDebug() << "show" << appWindow_.pos();
    appWindow_.oldPosition = appWindow_.pos();

    appWindow_.setWindowFlags(appWindow_.windowFlags() ^ Qt::Tool);
    appWindow_.show();
    appWindow_.setWindowState((appWindow_.windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
}

void AppController::showSettings()
{
    settingsWindow_.show();
    settingsWindow_.raise();
}

void AppController::trayIconDoubleClick(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::DoubleClick && !appWindow_.isVisible()) {
        show();
    }
}

void AppController::showTrayIcon()
{
    trayIcon = new QSystemTrayIcon(this);
    trayIconMenu = new QMenu();

    actionSettings = new QAction("Settings", this);
    trayIconMenu->addAction(actionSettings);
    connect(actionSettings, SIGNAL(triggered()), this, SLOT(showSettings()));

    trayIconMenu->addSeparator();

    actionQuit = new QAction("Quit", this);
    trayIconMenu->addAction(actionQuit);
    connect(actionQuit, SIGNAL(triggered()), this, SLOT(quit()));


    connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(trayIconDoubleClick(QSystemTrayIcon::ActivationReason)));

    trayIcon->setIcon(QIcon(":/images/images/itchio-icon-16.png"));
    trayIcon->setContextMenu (trayIconMenu);
    trayIcon->show();
}

void AppController::showTrayIconNotification(TrayNotifications notification, int duration)
{
    if (trayIcon->supportsMessages()) {
        switch(notification) {
        case NOTIFICATION_TEST:
            trayIcon->showMessage("Title", "Test", QSystemTrayIcon::Information, duration);
            break;
        }
    }
}

void AppController::showAppWindow()
{
    appWindow_.show();
}

void AppController::onLogin()
{
    if (settings_.autoLogin()) {
        settings_.setApiKey(api_.userKey);
        settings_.setUsername(api_.userName);
    }

    appWindow_.loginWidget->hide();
    appWindow_.loginWidget->deleteLater();
    appWindow_.setupLibrary();
}
