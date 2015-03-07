#include "gameframe.h"
#include "ui_gameframe.h"

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

GameFrame::GameFrame(QWidget* const parent, const Game& game, const DownloadKey& key, AppController* const controller)
    : QWidget(parent)
    , ui(new Ui::GameFrame)
    , game(game)
    , downloadKey(key)
    , controller(controller)
{
    ui->setupUi(this);

    networkManager = new QNetworkAccessManager(this);

    downloadMenu = new QMenu("Choose Download");
    ui->downloadButton->setMenu(downloadMenu);
    connect(downloadMenu, &QMenu::aboutToShow, this, &GameFrame::onTriggerDownloadMenu);

    ui->gameCoverLabel->setFixedWidth(
        int(ui->gameCoverLabel->maximumHeight() * double(Game::COVER_WIDTH) / Game::COVER_HEIGHT));

    ui->gameTitleLabel->setText(game.title);
    ui->gameCreatorLabel->setText(game.user.nameForDisplay());

    refreshThumbnail();
}

GameFrame::~GameFrame()
{
    delete ui;
}

void GameFrame::onClickDownload()
{
    qDebug() << "clicked download" << game.title;
}

void GameFrame::onDownloadThumbnail()
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

void GameFrame::onTriggerDownloadMenu()
{
    downloadMenu->clear();

    QAction* loaderAction = new QAction("Loading...", downloadMenu);

    loaderAction->setDisabled(true);
    downloadMenu->addAction(loaderAction);

    controller->api->downloadKeyUploads(downloadKey, [this](QList<Upload> uploads) {
        onUploads(uploads);
    });
}

void GameFrame::onTriggerUpload()
{
    isDownloading = true;
    ui->downloadButton->setEnabled(false);

    QAction* action = qobject_cast<QAction*>(sender());

    int pos = action->data().toInt();

    Upload upload = pendingUploads[pos];

    controller->api->downloadUpload(downloadKey, upload, [=](QString url) {
        QString path = QCoreApplication::applicationDirPath() + "/Downloads/" + game.title;

        QString fname = upload.filename;
        QStringList fdName = fname.split(".");
        QString fullPath = path + "/" + fdName.at(0)+ " " + fdName.at(1) + "/";
        QDir().mkpath(fullPath);

        qDebug() << "Download: " << url << "to" << fullPath;

        QFile* file = new QFile(fullPath + fname);
        file->open(QIODevice::WriteOnly);

        QNetworkRequest request;
        request.setUrl(QUrl(url));
        request.setHeader(QNetworkRequest::UserAgentHeader, ItchioApi::USER_AGENT);
        QNetworkReply* reply = networkManager->get(request);

        connect(reply, &QNetworkReply::downloadProgress, this, &GameFrame::downloadProgress);

        connect(reply, &QNetworkReply::readyRead, [=] {
            qDebug() << "ready read" << reply->bytesAvailable();
            file->write(reply->read(reply->bytesAvailable()));
        });

        connect(reply, &QNetworkReply::finished, [=] {
            reply->deleteLater();
            qDebug() << "finished" << fullPath;
            file->close();
            delete file;

            isDownloading = false;
            ui->downloadButton->setEnabled(true);
        });

    });
}

void GameFrame::onUploads(const QList<Upload>& uploads)
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

        connect(uploadAction, &QAction::triggered, this, &GameFrame::onTriggerUpload);

        downloadMenu->addAction(uploadAction);
    }
}

void GameFrame::refreshThumbnail()
{
    if (game.coverImageUrl == "") {
        return;
    }

    qDebug() << "Fetching cover" << game.coverImageUrl;

    QNetworkRequest request;
    request.setUrl(QUrl(game.coverImageUrl));
    request.setHeader(QNetworkRequest::UserAgentHeader, ItchioApi::USER_AGENT);

    QNetworkReply* reply = networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, &GameFrame::onDownloadThumbnail);
}

void GameFrame::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    ui->progressBar->setMaximum(bytesTotal);
    ui->progressBar->setValue(bytesReceived);
}

