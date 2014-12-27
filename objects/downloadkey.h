#ifndef DOWNLOADKEY_H
#define DOWNLOADKEY_H

#include "objects/game.h"

namespace itchio {

class DownloadKey
{
public:
    DownloadKey();

    unsigned int id;
    Game game;

    static DownloadKey fromJson(const QJsonObject &object);
};

} // namespace itchio

#endif // DOWNLOADKEY_H
