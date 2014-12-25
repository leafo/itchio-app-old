#ifndef DOWNLOADKEY_H
#define DOWNLOADKEY_H

#include <QObject>
#include <QJsonObject>
#include <objects/game.h>

class DownloadKey
{
public:
    DownloadKey();

    unsigned int id;
    Game game;

    static DownloadKey fromJson(const QJsonObject &object);
};

#endif // DOWNLOADKEY_H
