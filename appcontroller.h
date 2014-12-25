#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <QApplication>
#include <QWidget>
#include <QObject>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QIcon>
#include <QAction>
#include <QSettings>
#include <QVector>

#include "itchioapi.h"
#include "traynotifications.h"
#include "settings.h"
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

    void showTrayIcon();
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
