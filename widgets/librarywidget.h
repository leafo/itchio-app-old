#ifndef LIBRARYWIDGET_H
#define LIBRARYWIDGET_H

#include <QWidget>

#include "appcontroller.h"
#include "gamerow.h"

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
    void onMyOwnedKeys(QList<DownloadKey> downloadKeys);

private:
    Ui::LibraryWidget* const ui;
    AppController* const controller;

    void addGamesTab(const QString& title, const QList<GameRow *>& gameRows);
};

#endif // LIBRARYWIDGET_H
