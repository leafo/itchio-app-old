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

    static Game fromJson(QJsonObject& object);

    static int COVER_WIDTH;
    static int COVER_HEIGHT;
};

#endif // GAME_H
