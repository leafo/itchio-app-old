#ifndef GAMEROW_H
#define GAMEROW_H

#include <QWidget>
#include "objects/game.h"

namespace Ui {
class GameRow;
}

class GameRow : public QWidget
{
    Q_OBJECT

public:
    explicit GameRow(QWidget *parent, Game game);
    ~GameRow();

private slots:
    void onClickDownload();

private:
    Game game;
};

#endif // GAMEROW_H
