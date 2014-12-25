#include "game.h"
#include <QDebug>
#include <QJsonObject>

Game::Game()
{
}

Game Game::fromJson(const QJsonObject &object)
{
    Game game;

    game.id = object["id"].toInt();
    game.url = object["url"].toString();
    game.title = object["title"].toString();
    game.shortText = object["short_text"].toString();
    game.coverImageUrl = object["cover_url"].toString();
    game.user = User::fromJson(object["user"].toObject());

    return game;
}
