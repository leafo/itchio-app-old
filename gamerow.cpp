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
#include <QStandardPaths>
#include <QDir>
#include <QFile>

GameRow::GameRow(QWidget* const parent, const Game& game, const DownloadKey& key, AppController* const controller)
    : QWidget(parent)
    , game(game)
    , downloadKey(key)
    , controller(controller)
{
    networkManager = new QNetworkAccessManager(this);

    QHBoxLayout* rowLayout = new QHBoxLayout;
    downloadButton = new QPushButton("Download");

    downloadMenu = new QMenu("Choose download");
    downloadButton->setMenu(downloadMenu);
    connect(downloadMenu, &QMenu::aboutToShow, this, &GameRow::onTriggerDownloadMenu);

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

void GameRow::onTriggerDownloadMenu()
{
    downloadMenu->clear();
    QAction* loaderAction = new QAction("Loading...", downloadMenu);
    loaderAction->setDisabled(true);
    downloadMenu->addAction(loaderAction);
    controller->api.downloadKeyUploads(downloadKey, [this](QList<Upload> uploads) {
        onUploads(uploads);
    });
}

void GameRow::onTriggerUpload()
{
    QAction* action = qobject_cast<QAction*>(sender());
    int pos = action->data().toInt();
    Upload upload = pendingUploads[pos];
    controller->api.downloadUpload(downloadKey, upload, [=](QString url) {
//TODO This is a temporary fix to support systems that don't have Qt 5.4 yet (e.g. Debian as of January 2, 2015).
//TODO It should be removed when Qt 5.4 is readily available (e.g. via a package manager).
//TODO Additionally, a minimum version check should be added to itchio.pri.
#if QT_VERSION >= 0x050400
        QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
#else
    QString path = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
#endif
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

    connect(reply, &QNetworkReply::readyRead, [=] {
            qDebug() << "ready read" << reply->bytesAvailable();
            file->write(reply->read(reply->bytesAvailable())); });

    connect(reply, &QNetworkReply::finished, [=] {
            reply->deleteLater();
            qDebug() << "finished" << fullPath;
            file->close();
            delete file; });

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
