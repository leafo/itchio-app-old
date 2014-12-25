#include <QDebug>
#include "appcontroller.h"
#include "appwindow.h"
#include "secondarywindow.h"
#include "widgets/loginwidget.h"
#include "widgets/librarywidget.h"
#include "widgets/secondary/settingswidget.h"

//TODO: Minimizing to tray and restoring the window multiple times, after moving it for the first time and while not maximized, cause the window to move if taskbars are present. Cause not known.

AppController::AppController(QObject *parent) :
    QObject(parent)
{
    setupSettings();
    api = new ItchioApi(this, settings->loadSetting(API_URL));

    if(settings->loadSetting(KEEP_LOGGED_IN) == "1" && settings->loadSetting(API_KEY) != "") {
        api->loginWithApiKey(settings->loadSetting(API_KEY));
    }

    showTrayIcon();
    showAppWindow();
}

void AppController::setupSettings()
{
    settingsFile = "settings.scratch";
    settings = new AppSettings(settingsFile, QSettings::IniFormat);
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
            && !appWindow->isVisible()) {
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

void AppController::showAppWindow()
{
    appWindow = new AppWindow(this);

    appWindow->show();

    //secondaryWindows.append(new SecondaryWindow(new SettingsWidget(this), this));
    //secondaryWindows.value(0)->show();
}

void AppController::onLogin()
{
    if(settings->loadSetting((KEEP_LOGGED_IN)) == "1")
    {
        settings->saveSetting(API_KEY, api->userKey);
        settings->saveSetting(USERNAME, api->userName);
    }

    appWindow->loginWidget->hide();
    appWindow->loginWidget->deleteLater();
    appWindow->setupLibrary();
}
