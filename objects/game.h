#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <objects/user.h>

class Game
{
public:
    Game();
    unsigned int id;
    QString title;
    QString url;
    QString shortText;
    QString coverImageUrl;
    User user;

    static Game fromJson(const QJsonObject& object);

    static const int COVER_WIDTH = 315;
    static const int COVER_HEIGHT = 250;
};

#endif // GAME_H
