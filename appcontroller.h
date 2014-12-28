#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>

#include "itchioapi.h"
#include "traynotifications.h"
#include "appsettings.h"

class AppWindow;
class SecondaryWindow;

class AppController : public QObject
{
    Q_OBJECT

public:
    explicit AppController(QObject* const parent = 0);

    ItchioApi* api;

    AppSettings* settings;

    void setupTrayIcon();
    void showTrayIconNotification(TrayNotifications notification, int duration);
    void setupAppWindow();

private:
    QString settingsFile;

    QAction* actionQuit;
    QAction* actionSettings;

    AppWindow* appWindow;
    SecondaryWindow* loginWindow;
    SecondaryWindow* settingsWindow;

    QSystemTrayIcon* trayIcon;
    QMenu* trayIconMenu;

    bool loginWithApiKey;

    void setupLogin();
    void setupSettings();

signals:

public slots:
    void show();
    void hide();
    void quit();
    void showSettings();

    void trayIconDoubleClick(QSystemTrayIcon::ActivationReason reason);
    void setupTrayIconMenu(bool beforeLogin = false);

private slots:
    void onLogin();
    void onLoginFailure(QString error);
};

#endif // APPCONTROLLER_H
