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

    void onLogin();

    void setupTrayIcon();
    void showTrayIconNotification(TrayNotifications notification, int duration);
    void showAppWindow();

private:
    QString settingsFile;

    QAction* actionQuit;
    QAction* actionSettings;

    AppWindow* appWindow;
    SecondaryWindow* settingsWindow;

    QSystemTrayIcon* trayIcon;
    QMenu* trayIconMenu;

    void setupSettings();
    void setupTrayIconMenu(bool beforeLogin = false);

signals:

public slots:
    void show();
    void hide();
    void quit();
    void showSettings();

    void trayIconDoubleClick(QSystemTrayIcon::ActivationReason reason);

private slots:

};

#endif // APPCONTROLLER_H
