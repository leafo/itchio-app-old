#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QApplication>

#include "itchioapi.h"
#include "traynotifications.h"
#include "appsettings.h"

class AppWindow;
class SecondaryWindow;

class AppController : public QApplication
{
    Q_OBJECT

public:
    AppController(int& argc, char** argv);

    AppSettings settings;
    ItchioApi api;

    void setupTrayIcon();
    void showTrayIconNotification(TrayNotifications notification, int duration);
    void setupAppWindow();
    void onLogin();

private:
    QAction* actionQuit;
    QAction* actionSettings;

    AppWindow* appWindow;
    SecondaryWindow* loginWindow;
    SecondaryWindow* settingsWindow;

    QSystemTrayIcon trayIcon;
    QMenu* trayIconMenu;

    bool loginWithApiKey;

    void setupLogin();
    void onAutoLoginFailure(QString error);

    static QString loadStyleSheet();
signals:

public slots:
    void showSettings();

    void trayIconDoubleClick(QSystemTrayIcon::ActivationReason reason);
    void setupTrayIconMenu(bool beforeLogin = false);

};

#endif // APPCONTROLLER_H
