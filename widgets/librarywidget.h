#ifndef LIBRARYWIDGET_H
#define LIBRARYWIDGET_H

#include <QWidget>
#include <QList>
#include <QGridLayout>
#include <QResizeEvent>

#include "appcontroller.h"
#include "elements/gameframe.h"

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

    QList<QVBoxLayout*> tabLayouts;
    QList<QList<QVBoxLayout*>*> tabRowLayouts;
    QList<QList<QHBoxLayout*>*> tabColLayouts;
    QList<QList<GameFrame*>*> tabWidgets;
    int tabSetupCount = 0;
    int gameFrameWidth;

    void resizeEvent(QResizeEvent *event);

    void adjustTabLayouts();

    void addGamesTab(const QString& title, const QList<GameFrame *>& gameFrames, int tab);
};

#endif // LIBRARYWIDGET_H
