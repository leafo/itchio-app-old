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

AppController::AppController(QObject* parent)
    : QObject(parent)
    , settingsWindow(NULL)
    , loginWithApiKey(false)
{
    setupSettings();
    api = new ItchioApi(this, settings->apiUrl());

    setupTrayIcon();
    setupAppWindow();

    if (settings->autoLogin() && settings->hasValidApiKey()) {
        api->loginWithApiKey(settings->apiKey(), [this](bool success, QString err) {
            if (success) {
                onLogin();
            } else {
                onAutoLoginFailure(err);
            }
        });

        loginWithApiKey = true;
    } else {
        setupLogin();
    }

    settingsWindow = new SecondaryWindow(new SettingsWidget(this), this, false);

}

void AppController::setupSettings()
{
    settingsFile = QCoreApplication::applicationDirPath() + "/itchio.ini";
    settings = new AppSettings(settingsFile, QSettings::IniFormat, this);
}

void AppController::quit()
{
    settings->enableStartMaximized(appWindow->isMaximized);
    settings->setWindowGeometry(appWindow->saveGeometry());
    settings->setWindowOldSize(appWindow->oldSize);
    settings->setWindowOldPosition(appWindow->oldPosition);

    if (settings->autoLogin()) {
        settings->setApiKey(api->userKey);
        settings->setUsername(api->userName);
    }

    QCoreApplication::exit();
}

void AppController::showSettings()
{
    settingsWindow->show();
    settingsWindow->activateWindow();
}

void AppController::trayIconDoubleClick(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::DoubleClick && !appWindow->isVisible()) {
        appWindow->showWindow();
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
    trayIcon->setContextMenu(trayIconMenu);

    if (!beforeLogin) {
        QAction* actionSettings = new QAction("Settings", this);
        trayIconMenu->addAction(actionSettings);
        connect(actionSettings, SIGNAL(triggered()), this, SLOT(showSettings()));

        trayIconMenu->addSeparator();
    }

    QAction* actionQuit = new QAction("Quit", this);
    trayIconMenu->addAction(actionQuit);
    connect(actionQuit, SIGNAL(triggered()), this, SLOT(quit()));

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(trayIconDoubleClick(QSystemTrayIcon::ActivationReason)));
}

void AppController::showTrayIconNotification(TrayNotifications::Notifications notification, QString data)
{
    if (settings->showTrayNotifications()) {
        if((notification == TrayNotifications::LIBRARY_UPDATE &&
            settings->showLibraryUpdateNotifications()) ||
                (notification == TrayNotifications::DOWNLOAD_FINISHED &&
                 settings->showDownloadFinishedNotifications()) ||
                (notification == TrayNotifications::GAME_UPDATE_AVAILABLE &&
                 settings->showGameUpdateAvailableNotifications())){

            trayIcon->showMessage(TrayNotifications::toString(notification),
                                  data, QSystemTrayIcon::NoIcon, 5000);
        }


    }
}

void AppController::setupLogin()
{
    settings->setApiKey("");
    api->userKey = "";

    setupTrayIconMenu(true);

    loginWindow = new SecondaryWindow(new LoginWidget(qobject_cast<QWidget*>(this), this), this);
    loginWindow->show();
}

void AppController::setupAppWindow()
{
    appWindow = new AppWindow(this);
}

void AppController::onLogin()
{
    setupTrayIconMenu();

    if (!loginWithApiKey) {
        loginWindow->deleteLater();
        loginWindow->close();
    }

    appWindow->setupLibrary();
}

void AppController::onAutoLoginFailure(QString)
{
    setupLogin();
}
