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
#include "appwindow.h"
#include "secondarywindow.h"

namespace itchio {

class AppController : public QApplication
{
    Q_OBJECT

public:
    AppController(int& argc, char** argv);

    inline Settings& settings(){ return settings_; }
    inline const Settings& const_settings() const { return settings_; }

    inline Api& api(){ return api_; }
    inline const Api& const_api() const { return api_; }

    void onLogin();

    void showTrayIcon();
    void showTrayIconNotification(TrayNotifications notification, int duration);
    void showAppWindow();

private:
    Settings settings_;
    Api api_;

    QAction* actionQuit;
    QAction* actionSettings;

    AppWindow appWindow_;
    SecondaryWindow settingsWindow_;

    QSystemTrayIcon* trayIcon;
    QMenu* trayIconMenu;

    void setupSettings();

signals:

public slots:
    void show();
    void hide();
    void showSettings();

    void trayIconDoubleClick(QSystemTrayIcon::ActivationReason reason);

private slots:
};

} // namespace itchio

#endif // APPCONTROLLER_H
