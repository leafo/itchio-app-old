#ifndef LIBRARYWIDGET_H
#define LIBRARYWIDGET_H

#include <QWidget>

#include "appcontroller.h"
#include "elements/gamerow.h"

namespace Ui
{
class LibraryWidget;
}

class LibraryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LibraryWidget(QWidget *parent, AppController* controller);
    ~LibraryWidget();


public slots:
    void onMyPurchasedKeys(QList<DownloadKey> downloadKeys);
    void onMyClaimedKeys(QList<DownloadKey> downloadKeys);

private:
    Ui::LibraryWidget* const ui;
    AppController* const controller;

    void addGamesTab(const QString& title, const QList<GameRow *>& gameRows);
};

#endif // LIBRARYWIDGET_H
