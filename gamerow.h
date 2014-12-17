#ifndef GAMEROW_H
#define GAMEROW_H

#include <QWidget>
#include <QLabel>
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
    void onDownloadThumbnail();

private:
    Game game;
    QLabel* imageHolder;

    void refreshThumbnail();
};

#endif // GAMEROW_H
