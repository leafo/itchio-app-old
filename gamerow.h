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
    void onDownloadKeyUploads(DownloadKey key, QList<Upload> uploads);

private:
    Game game;
    DownloadKey downloadKey;
    AppController* controller;

    QLabel* imageHolder;
    QProgressBar* downloadProgress;
    QPushButton* downloadButton;
    QMenu* downloadMenu;

    void refreshThumbnail();
};

#endif // GAMEROW_H
