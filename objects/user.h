#ifndef USER_H
#define USER_H

#include <QObject>

class User
{
public:
    User();

    unsigned int id;
    QString username;
    QString displayName;
    QString url;
    QString avatarUrl;

    QString nameForDisplay() const;

    static User fromJson(const QJsonObject& object);
};

#endif // USER_H
