#include "user.h"

#include <QJsonObject>

User::User()
{
}

QString User::nameForDisplay() const
{
    if (displayName == "") {
        return username;
    } else {
        return displayName;
    }
}

User User::fromJson(const QJsonObject &object)
{
    User user;

    user.id = object["id"].toInt();
    user.url = object["url"].toString();
    user.username = object["username"].toString();
    user.displayName = object["display_name"].toString();
    user.avatarUrl = object["cover_url"].toString();

    return user;
}
