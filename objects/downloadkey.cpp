#include "downloadkey.h"

DownloadKey::DownloadKey()
{
}

DownloadKey DownloadKey::fromJson(const QJsonObject &object)
{
    DownloadKey key;

    key.id = object["id"].toInt();
    key.game = Game::fromJson(object["game"].toObject());

    return key;
}
