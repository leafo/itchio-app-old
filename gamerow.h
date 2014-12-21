#ifndef GAMEROW_H
#define GAMEROW_H

#include <QWidget>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>

#include "objects/game.h"

namespace Ui
{
class GameRow;
}

class GameRow : public QWidget
{
    Q_OBJECT

public:
    explicit GameRow(QWidget *parent, Game game);
    ~GameRow();

    static int COVER_HEIGHT;

private slots:
    void onClickDownload();
    void onDownloadThumbnail();

private:
    Game game;
    QLabel* imageHolder;
    QProgressBar* downloadProgress;
    QPushButton* downloadButton;

    void refreshThumbnail();
};

#endif // GAMEROW_H
