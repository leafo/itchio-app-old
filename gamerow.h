#ifndef GAMEROW_H
#define GAMEROW_H

#include <QWidget>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>

#include "appcontroller.h"
#include "objects/game.h"

namespace Ui
{
class GameRow;
}

class GameRow : public QWidget
{
    Q_OBJECT

public:
    explicit GameRow(QWidget *parent, Game game, DownloadKey key, AppController* controller);
    ~GameRow();

    static int COVER_HEIGHT;

private slots:
    void onClickDownload();
    void onDownloadThumbnail();
    void onTriggerMenu();

private:
    AppController* controller;

    Game game;
    DownloadKey downloadKey;

    QLabel* imageHolder;
    QProgressBar* downloadProgress;
    QPushButton* downloadButton;
    QMenu* downloadMenu;

    void refreshThumbnail();
};

#endif // GAMEROW_H
