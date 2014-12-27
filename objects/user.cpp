#include "user.h"
#include <QJsonObject>

using itchio::User;

User::User()
{
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
