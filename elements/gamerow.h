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
    explicit GameRow(QWidget* const parent, const Game& game, const DownloadKey& key, AppController* const controller);
    ~GameRow();

private:
    Ui::GameRow *ui;

    QNetworkAccessManager* networkManager;

    Game game;
    DownloadKey downloadKey;
    AppController* const controller;

    QMenu* downloadMenu;

    QList<Upload> pendingUploads;

    void refreshThumbnail();

private slots:
    void onClickDownload();
    void onDownloadThumbnail();
    void onTriggerDownloadMenu();
    void onTriggerUpload();
    void onUploads(const QList<Upload>& uploads);
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);

};

#endif // GAMEROW_H
