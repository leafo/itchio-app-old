#ifndef UPLOAD_H
#define UPLOAD_H

#include <QObject>
#include <QJsonObject>

class Upload
{
public:
    Upload();

    unsigned int id;
    unsigned int gameId;
    QString filename;
    QString displayName;

    unsigned int size;

    bool pWindows;
    bool pLinux;
    bool pOsx;
    bool pAndroid;

    static Upload fromJson(const QJsonObject& object);
};

#endif // UPLOAD_H
