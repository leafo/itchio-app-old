#ifndef USER_H
#define USER_H

#include <QString>

class QJsonObject;

namespace itchio {

class User
{
public:
    User();

    unsigned int id;
    QString username;
    QString displayName;
    QString url;
    QString avatarUrl;

    inline QString nameForDisplay() const
    {
        return displayName != "" ? displayName : username;
    }

    static User fromJson(const QJsonObject& object);
};

} // namespace itchio

#endif // USER_H
