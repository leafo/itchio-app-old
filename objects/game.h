#ifndef GAME_H
#define GAME_H

#include <QObject>

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(QObject *parent = 0);
    int id;
    QString title;
    QString url;
    QString shortText;
    QString coverImageUrl;

signals:

public slots:

};

#endif // GAME_H
