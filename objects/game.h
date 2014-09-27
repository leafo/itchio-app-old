#ifndef GAME_H
#define GAME_H

#include <QObject>

class Game
{
public:
    Game();
    int id;
    QString title;
    QString url;
    QString shortText;
    QString coverImageUrl;
};

#endif // GAME_H
