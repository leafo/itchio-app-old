#include <QApplication>
#include <QSettings>
#include <QIcon>

#include <QDebug>

#include "appcontroller.h"
#include "appwindow.h"
#include "secondarywindow.h"
#include "widgets/librarywidget.h"
#include "widgets/secondary/loginwidget.h"
#include "widgets/secondary/settingswidget.h"

//TODO: Create custom maximizing pipeline to better handle taskbars.

AppController::AppController(QObject *parent) :
    QObject(parent),
    settingsWindow(NULL),
    loginWithApiKey(false)
{
    setupSettings();
    api = new ItchioApi(this, settings->apiUrl());

    setupTrayIcon();
    setupAppWindow();

    connect(api, SIGNAL(onLogin()), this, SLOT(onLogin()));

    if(settings->autoLogin() && settings->hasValidApiKey()) {
        connect(api, SIGNAL(onLoginFailure(QString)), this, SLOT(onLoginFailure(QString)));

        api->loginWithApiKey(settings->apiKey());

        loginWithApiKey = true;
    } else {
        setupLogin();
    }
}

void AppController::setupSettings()
{
    settingsFile = "itchio.ini";
    settings = new AppSettings(settingsFile, QSettings::IniFormat, this);
}

void AppController::hide()
{
    if(!appWindow->oldPosition.isNull()) {
        appWindow->move(appWindow->oldPosition);
    }

    appWindow->showMinimized();

    appWindow->setWindowFlags(appWindow->windowFlags() ^ Qt::Tool);
}

void AppController::show()
{
    appWindow->oldPosition = appWindow->pos();

    appWindow->setWindowFlags(appWindow->windowFlags() ^ Qt::Tool);
    appWindow->show();
    appWindow->setWindowState((appWindow->windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
}

void AppController::quit()
{
    QCoreApplication::exit();
}

void AppController::showSettings()
{
    settingsWindow = new SecondaryWindow(new SettingsWidget(this), this);

    settingsWindow->show();
    settingsWindow->raise();
}

void AppController::trayIconDoubleClick(QSystemTrayIcon::ActivationReason reason)
{
    if(reason == QSystemTrayIcon::DoubleClick && !appWindow->isVisible()) {
        show();
    }
}

void AppController::setupTrayIcon()
{
    trayIcon = new QSystemTrayIcon(this);

    trayIcon->setIcon(QIcon(":/images/images/itchio-icon-16.png"));
    trayIcon->show();
}

void AppController::setupTrayIconMenu(bool beforeLogin)
{
    trayIconMenu = new QMenu();
    trayIcon->setContextMenu (trayIconMenu);

    if(!beforeLogin) {
        actionSettings = new QAction("Settings", this);
        trayIconMenu->addAction(actionSettings);
        connect(actionSettings, SIGNAL(triggered()), this, SLOT(showSettings()));

        trayIconMenu->addSeparator();
    }

    actionQuit = new QAction("Quit", this);
    trayIconMenu->addAction(actionQuit);
    connect(actionQuit, SIGNAL(triggered()), this, SLOT(quit()));

    connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(trayIconDoubleClick(QSystemTrayIcon::ActivationReason)));
}

void AppController::showTrayIconNotification(TrayNotifications notification, int duration)
{
    if(settings->showTrayNotifications()) {
        switch(notification) {
        case NOTIFICATION_TEST:
            trayIcon->showMessage("Title", "Test", QSystemTrayIcon::Information, duration);
            break;
        }
    }
}

void AppController::setupLogin()
{
    settings->setApiKey("");
    api->userKey = "";

    setupTrayIconMenu(true);

    loginWindow = new SecondaryWindow(new LoginWidget(qobject_cast<QWidget *>(this), this), this);
    loginWindow->show();
}

void AppController::setupAppWindow()
{
    appWindow = new AppWindow(this);
}

void AppController::onLogin()
{
    if(settings->autoLogin()) {
        settings->setApiKey(api->userKey);
        settings->setUsername(api->userName);
    }

    setupTrayIconMenu();

    if(!loginWithApiKey) {
        loginWindow->deleteLater();
        loginWindow->close();
    }

    appWindow->setupLibrary();
}

void AppController::onLoginFailure(QString error)
{
    if(error == "invalid key") {
        setupLogin();
    }
}
