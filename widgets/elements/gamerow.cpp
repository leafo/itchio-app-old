#include "gamerow.h"
#include "ui_gamerow.h"

#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QUrlQuery>
#include <QMenu>
#include <QAction>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QPixmap>

#include <QDebug>

#include "itchioapi.h"
#include <QStandardPaths>
#include <QDir>
#include <QFile>

GameRow::GameRow(QWidget* const parent, const Game& game, const DownloadKey& key, AppController* const controller)
    : QWidget(parent)
    , ui(new Ui::GameRow)
    , game(game)
    , downloadKey(key)
    , controller(controller)
{
    ui->setupUi(this);

    networkManager = new QNetworkAccessManager(this);

    downloadMenu = new QMenu("Choose Download");
    ui->downloadButton->setMenu(downloadMenu);
    connect(downloadMenu, &QMenu::aboutToShow, this, &GameRow::onTriggerDownloadMenu);

    ui->gameCoverLabel->setFixedWidth(
        int(ui->gameCoverLabel->maximumHeight() * double(Game::COVER_WIDTH) / Game::COVER_HEIGHT));

    ui->gameTitleLabel->setText(game.title);
    ui->gameCreatorLabel->setText(game.user.nameForDisplay());

    refreshThumbnail();
}

GameRow::~GameRow()
{
    delete ui;
}

void GameRow::onClickDownload()
{
    qDebug() << "clicked download" << game.title;
}

void GameRow::onDownloadThumbnail()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    reply->deleteLater();

    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Error downloading thumbnail" << reply->errorString();
        return;
    }

    QByteArray imageData = reply->readAll();
    QPixmap pixmap;
    if (pixmap.loadFromData(imageData)) {
        ui->gameCoverLabel->setPixmap(pixmap);
    }
}

void GameRow::onTriggerDownloadMenu()
{
    downloadMenu->clear();

    QAction* loaderAction = new QAction("Loading...", downloadMenu);

    loaderAction->setDisabled(true);
    downloadMenu->addAction(loaderAction);

    controller->api->downloadKeyUploads(downloadKey, [this](QList<Upload> uploads) {
        onUploads(uploads);
    });
}

void GameRow::onTriggerUpload()
{
    QAction* action = qobject_cast<QAction*>(sender());

    int pos = action->data().toInt();

    Upload upload = pendingUploads[pos];

    controller->api->downloadUpload(downloadKey, upload, [=](QString url) {
        QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
        QDir().mkpath(path);

        QString fname = QString::number(upload.id);
        QString fullPath = path + "/" + fname;

        qDebug() << "Download: " << url << "to" << fullPath;

        QFile* file = new QFile(fullPath);
        file->open(QIODevice::WriteOnly);

        QNetworkRequest request;
        request.setUrl(QUrl(url));
        request.setHeader(QNetworkRequest::UserAgentHeader, ItchioApi::USER_AGENT);
        QNetworkReply* reply = networkManager->get(request);

        connect(reply, &QNetworkReply::downloadProgress, this, &GameRow::downloadProgress);

        connect(reply, &QNetworkReply::readyRead, [=] {
            qDebug() << "ready read" << reply->bytesAvailable();
            file->write(reply->read(reply->bytesAvailable()));
        });

        connect(reply, &QNetworkReply::finished, [=] {
            reply->deleteLater();
            qDebug() << "finished" << fullPath;
            file->close();
            delete file;
        });

    });
}

void GameRow::onUploads(const QList<Upload>& uploads)
{
    pendingUploads = uploads;
    downloadMenu->clear();

    if (uploads.empty()) {
        QAction* loaderAction = new QAction("No files", downloadMenu);
        loaderAction->setDisabled(true);
        downloadMenu->addAction(loaderAction);
        return;
    }

    for (int i = 0; i < uploads.count(); i++) {
        QAction* const uploadAction = new QAction(uploads[i].filename, downloadMenu);
        uploadAction->setData(i);

        connect(uploadAction, &QAction::triggered, this, &GameRow::onTriggerUpload);

        downloadMenu->addAction(uploadAction);
    }
}

void GameRow::refreshThumbnail()
{
    if (game.coverImageUrl == "") {
        return;
    }

    qDebug() << "Fetching cover" << game.coverImageUrl;

    QNetworkRequest request;
    request.setUrl(QUrl(game.coverImageUrl));
    request.setHeader(QNetworkRequest::UserAgentHeader, ItchioApi::USER_AGENT);

    QNetworkReply* reply = networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, &GameRow::onDownloadThumbnail);
}

void GameRow::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    ui->progressBar->setMaximum(bytesTotal);
    ui->progressBar->setValue(bytesReceived);
}

