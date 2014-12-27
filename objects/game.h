#ifndef GAME_H
#define GAME_H

#include "objects/user.h"

namespace itchio {

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

    static const int COVER_WIDTH = 315;
    static const int COVER_HEIGHT = 250;

    static Game fromJson(const QJsonObject& object);
};

} // namespace itchio

#endif // GAME_H
