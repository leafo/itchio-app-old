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

#include "gamerow.h"
#include "itchioapi.h"

GameRow::GameRow(QWidget* const parent, const Game& game, const DownloadKey& key, AppController* const controller) :
    QWidget(parent),
    game(game),
    downloadKey(key),
    controller(controller)
{
    QHBoxLayout* rowLayout = new QHBoxLayout;
    downloadButton = new QPushButton("Download");

    downloadMenu = new QMenu("Choose download");
    downloadButton->setMenu(downloadMenu);
    connect(downloadMenu, SIGNAL(aboutToShow()), SLOT(onTriggerMenu()));
    connect(controller->api, SIGNAL(onDownloadKeyUploads(DownloadKey,QList<Upload>)),
            SLOT(onDownloadKeyUploads(DownloadKey,QList<Upload>)));

    imageHolder = new QLabel();
    double ratio = double(Game::COVER_WIDTH) / Game::COVER_HEIGHT;

    imageHolder->setFixedWidth(int(COVER_HEIGHT * ratio));
    imageHolder->setFixedHeight(COVER_HEIGHT);
    imageHolder->setScaledContents(true);
    imageHolder->setObjectName("imageHolder");

    downloadProgress = new QProgressBar();
    downloadProgress->setMinimum(0);
    downloadProgress->setMaximum(100);

    rowLayout->addWidget(imageHolder);


    QWidget* infoWidget = new QWidget();
    QVBoxLayout* infoWidgetLayout = new QVBoxLayout();
    infoWidgetLayout->addWidget(new QLabel(game.title));
    infoWidgetLayout->addWidget(new QLabel(game.user.nameForDisplay()));
    infoWidget->setLayout(infoWidgetLayout);

    rowLayout->addWidget(infoWidget, 1);
    rowLayout->addWidget(downloadButton, 0);

    setLayout(rowLayout);

    refreshThumbnail();
}

GameRow::~GameRow()
{
}

void GameRow::onClickDownload()
{
    qDebug() << "clicked download" << game.title;
    layout()->removeWidget(downloadButton);
    downloadButton->hide();

    qobject_cast<QHBoxLayout*>(layout())->addWidget(downloadProgress, 0);
    downloadProgress->setMaximum(0);
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
        imageHolder->setPixmap(pixmap);
    }
}

void GameRow::onTriggerMenu()
{
    downloadMenu->clear();
    QAction* loaderAction = new QAction("Loading...", downloadMenu);
    loaderAction->setDisabled(true);
    downloadMenu->addAction(loaderAction);
    controller->api->downloadKeyUploads(downloadKey);
}

void GameRow::onTriggerUpload()
{
    QAction* action = qobject_cast<QAction*>(sender());
    int pos = action->data().toInt();
    qDebug() << "triggered upload" << pos;
    Upload toDownload = pendingUploads[pos];
}

void GameRow::onDownloadKeyUploads(const DownloadKey& key, const QList<Upload>& uploads)
{
    // need to pass correct download key first
    // if (key.id != downloadKey.id) {
    //     return;
    // }

    pendingUploads = uploads;
    downloadMenu->clear();

    if (uploads.empty()) {
        QAction* loaderAction = new QAction("No files", downloadMenu);
        loaderAction->setDisabled(true);
        downloadMenu->addAction(loaderAction);
        return;
    }

    for (int i = 0; i < uploads.count(); i++) {
        QAction* const uploadAction =  new QAction(uploads[i].filename, downloadMenu);
        uploadAction->setData(i);
        connect(uploadAction, SIGNAL(triggered()), this, SLOT(onTriggerUpload()));
        downloadMenu->addAction(uploadAction);
    }
}

void GameRow::refreshThumbnail()
{
    if (game.coverImageUrl == "") {
        return;
    }

    QNetworkAccessManager* networkManager = new QNetworkAccessManager(this);

    qDebug() << "Fetching cover" << game.coverImageUrl;

    QNetworkRequest request;
    request.setUrl(QUrl(game.coverImageUrl));
    request.setHeader(QNetworkRequest::UserAgentHeader, ItchioApi::USER_AGENT);

    QNetworkReply* reply = networkManager->get(request);
    connect(reply, SIGNAL(finished()), this, SLOT(onDownloadThumbnail()));
}
