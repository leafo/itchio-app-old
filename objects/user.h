#ifndef USER_H
#define USER_H

#include <QObject>

class User
{
public:
    User();

    int id;
    QString username;
    QString displayName;
    QString url;
    QString avatarUrl;

    QString nameForDisplay();

    static User fromJson(QJsonObject& object);
};

#endif // USER_H
