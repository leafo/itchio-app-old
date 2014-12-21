#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <QApplication>
#include <QWidget>
#include <QObject>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QIcon>
#include <QAction>

#include "itchioapi.h"
#include "traynotifications.h"

class LoginDialog;
class GamesWindow;

class AppController : public QObject
{
    Q_OBJECT
public:
    explicit AppController(QObject *parent = 0);
    ItchioApi* api;

    void showTrayIcon();
    void showTrayIconNotification(TrayNotifications notification, int duration);
    void showLogin();
    void showGames();

signals:

public slots:
    void show();
    void hide();
    void quit();

    void trayIconDoubleLeftClick(QSystemTrayIcon::ActivationReason reason);

private slots:


private:
    QWidget* activeWindow;

    QSystemTrayIcon* trayIcon;
    QMenu* trayIconMenu;

    QAction* actionQuit;

    LoginDialog* loginDialog;
    GamesWindow* gamesWindow;

};

#endif // APPCONTROLLER_H
