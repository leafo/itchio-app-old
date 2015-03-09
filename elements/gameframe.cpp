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
#include "traynotifications.h"
#include <QStandardPaths>
#include <QDir>
#include <QFile>

GameFrame::GameFrame(QWidget* const parent, const Game& game, const DownloadKey& key, AppController* const controller)
    : QWidget(parent)
    , game(game)
    , ui(new Ui::GameFrame)
    , downloadKey(key)
    , controller(controller)
{
    ui->setupUi(this);

    networkManager = new QNetworkAccessManager(this);

    ui->gameCoverLabel->setFixedWidth(
        int(ui->gameCoverLabel->maximumHeight() * double(Game::COVER_WIDTH) / Game::COVER_HEIGHT));

    ui->gameTitleLabel->setText(game.title);
    ui->gameCreatorLabel->setText(game.user.nameForDisplay());

    refreshThumbnail();
    getDownloads();
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

    QDir().mkpath(coverCachePath);
    QFile coverCache(coverCachePath + QString::number(game.id));

    if(coverCache.open(QIODevice::WriteOnly)) {
        coverCache.write(imageData);
        coverCache.close();
    }
}

void GameFrame::onTriggerUpload()
{
    isDownloading = true;
    ui->downloadButton->setEnabled(false);

    QProgressBar* progressBar = new QProgressBar(this);
    progressBar->setObjectName("progressBar");
    progressBar->setTextVisible(false);
    progressBar->setMaximumHeight(20);
    progressBar->setMinimumWidth(180);

    ui->gameFrameLayout->removeWidget(ui->downloadButton);
    ui->downloadButton->setVisible(false);
    ui->gameFrameLayout->addWidget(progressBar, 0, Qt::AlignCenter);

    if(downloadPosition == -1){
        QAction* action = qobject_cast<QAction*>(sender());
        downloadPosition = action->data().toInt();
    }

    Upload upload = pendingUploads[downloadPosition];

    controller->api->downloadUpload(downloadKey, upload, [=](QString url) {
        QString path = downloadPath + game.title;

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

        connect(reply, &QNetworkReply::downloadProgress, [=](qint64 bytesReceived, qint64 bytesTotal) {
            progressBar->setMaximum(bytesTotal);
            progressBar->setValue(bytesReceived);
        });

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

            ui->gameFrameLayout->removeWidget(progressBar);
            progressBar->setVisible(false);
            progressBar->deleteLater();

            ui->downloadButton->setEnabled(true);
            ui->gameFrameLayout->addWidget(ui->downloadButton, 0, Qt::AlignCenter);
            ui->downloadButton->setVisible(true);

            controller->showTrayIconNotification(TrayNotifications::DOWNLOAD_FINISHED,
                                                 game.title + " - " + fname);
        });

    });
}

void GameFrame::refreshThumbnail()
{
    if (game.coverImageUrl == "") {
        return;
    }
    else{
        QFile coverCache(coverCachePath + QString::number(game.id));

        if(coverCache.exists() && coverCache.open(QIODevice::ReadOnly)) {
            QPixmap pixmap;
            if (pixmap.loadFromData(coverCache.readAll())) {
                ui->gameCoverLabel->setPixmap(pixmap);
            }

            coverCache.close();

            return;
        }


    }

    qDebug() << "Fetching cover" << game.coverImageUrl;

    QNetworkRequest request;
    request.setUrl(QUrl(game.coverImageUrl));
    request.setHeader(QNetworkRequest::UserAgentHeader, ItchioApi::USER_AGENT);

    QNetworkReply* reply = networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, &GameFrame::onDownloadThumbnail);
}

void GameFrame::getDownloads()
{
    controller->api->downloadKeyUploads(downloadKey, [this](QList<Upload> uploads) {
        if(uploads.size() == 0){
            QAction* emptyAction = new QAction("No files", downloadMenu);
            emptyAction->setDisabled(true);
            downloadMenu->addAction(emptyAction);
        }
        else if(uploads.size() == 1){
            pendingUploads = uploads;

            downloadPosition = 0;

            connect(ui->downloadButton, &QPushButton::pressed, this, &GameFrame::onTriggerUpload);
        }
        else{
            downloadMenu = new QMenu("Choose Download");
            ui->downloadButton->setMenu(downloadMenu);

            pendingUploads = uploads;

            for (int i = 0; i < uploads.count(); i++) {
                QAction* const uploadAction = new QAction(uploads[i].filename, downloadMenu);
                uploadAction->setData(i);

                connect(uploadAction, &QAction::triggered, this, &GameFrame::onTriggerUpload);

                downloadMenu->addAction(uploadAction);
            }
        }

        ui->downloadButton->setEnabled(true);
    });
}

void GameFrame::on_playButton_clicked()
{

}
