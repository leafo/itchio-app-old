#include "upload.h"

Upload::Upload()
{
}

Upload Upload::fromJson(const QJsonObject &object)
{
    Upload upload;

    upload.id = object["id"].toInt();
    upload.gameId = object["game_id"].toInt();
    upload.size = object["size"].toInt();

    upload.filename = object["filename"].toString();
    upload.displayName = object["display_name"].toString();

    upload.pWindows = object["p_windows"].toBool();
    upload.pLinux = object["p_linux"].toBool();
    upload.pOsx = object["p_osx"].toBool();
    upload.pAndroid = object["p_android"].toBool();

    return upload;
}

