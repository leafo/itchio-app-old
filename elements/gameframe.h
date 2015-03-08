#ifndef GAMEFRAME_H
#define GAMEFRAME_H

#include <QWidget>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>

#include "appcontroller.h"
#include "objects/game.h"

namespace Ui
{
class GameFrame;
}

class GameFrame : public QWidget
{
    Q_OBJECT

public:
    explicit GameFrame(QWidget* const parent, const Game& game, const DownloadKey& key, AppController* const controller);
    ~GameFrame();

private:
    Ui::GameFrame *ui;

    QNetworkAccessManager* networkManager;

    Game game;
    DownloadKey downloadKey;
    AppController* const controller;

    QMenu* downloadMenu;

    QList<Upload> pendingUploads;

    bool isDownloading = false;
    int downloadPosition = -1;

    void refreshThumbnail();
    void getDownloads();

private slots:
    void onClickDownload();
    void onDownloadThumbnail();
    void onTriggerUpload();
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);

};

#endif // GAMEFRAME_H
