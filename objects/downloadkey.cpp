#include "downloadkey.h"

DownloadKey::DownloadKey()
{
}


DownloadKey DownloadKey::fromJson(QJsonObject &object)
{
    DownloadKey key;

    key.id = object["id"].toInt();
    QJsonObject gameObject =  object["game"].toObject();
    key.game = Game::fromJson(gameObject);

    return key;
}
