#ifndef GAMEFRAME_H
#define GAMEFRAME_H

#include <QCoreApplication>
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

    Game game;

private:
    const QString downloadPath = QCoreApplication::applicationDirPath() + "/Downloads/";
    const QString coverCachePath = QCoreApplication::applicationDirPath() + "/Cache/Game Covers/";

    Ui::GameFrame *ui;

    QNetworkAccessManager* networkManager;

    DownloadKey downloadKey;
    AppController* const controller;

    QMenu* downloadMenu;

    QProgressBar* progressBar;

    QList<Upload> pendingUploads;

    int downloadPosition = -1;

    void refreshThumbnail();
    void getDownloads();

private slots:
    void onClickDownload();
    void onDownloadThumbnail();
    void onTriggerUpload();

    void on_playButton_clicked();
};

#endif // GAMEFRAME_H
