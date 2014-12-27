#ifndef UPLOAD_H
#define UPLOAD_H

#include <QString>

class QJsonObject;

namespace itchio {

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

} // namespace itchio

#endif // UPLOAD_H
