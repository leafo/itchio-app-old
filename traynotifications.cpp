#include "traynotifications.h"

TrayNotifications::TrayNotifications()
{

}

TrayNotifications::~TrayNotifications()
{

}

QString TrayNotifications::toString(const Notifications& notification)
{
    switch (notification) {
    case TrayNotifications::LIBRARY_UPDATE:
        return "Library Update Available!";
    case TrayNotifications::DOWNLOAD_FINISHED:
        return "Download Finished!";
    default:
        // This is a guard to make sure any keys added later on are handled in this switch-case.
        qFatal("[TrayNotifications::toStringList] Undefined key!");
    }
}
