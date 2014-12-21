#include "game.h"
#include <QDebug>
#include <QJsonObject>

int Game::COVER_WIDTH = 315;
int Game::COVER_HEIGHT = 250;

Game::Game()
{
}

Game Game::fromJson(QJsonObject &object)
{
    Game game;
    game.id = object["id"].toInt();
    game.url = object["url"].toString();
    game.title = object["title"].toString();
    game.shortText = object["short_text"].toString();
    game.coverImageUrl = object["cover_url"].toString();

    return game;
}
