#ifndef TRAYNOTIFICATIONS_H
#define TRAYNOTIFICATIONS_H

#include <QStringList>

class TrayNotifications
{
public:
    TrayNotifications();
    ~TrayNotifications();

    enum Notifications {
        LIBRARY_UPDATE,
        GAME_UPDATE_AVAILABLE,
        DOWNLOAD_FINISHED
    };

    static QString toString(const Notifications& notification);
};

#endif // TRAYNOTIFICATIONS_H
