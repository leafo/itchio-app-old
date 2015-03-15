#ifndef LIBRARYWIDGET_H
#define LIBRARYWIDGET_H

#include <QWidget>
#include <QList>
#include <QGridLayout>
#include <QResizeEvent>
#include <QScrollArea>
#include <QTimer>

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

    QList<QScrollArea*> tabScrollAreas;
    QList<QWidget*> tabWrappers;
    QList<QVBoxLayout*> tabLayouts;
    QList<QList<QVBoxLayout*>*> tabRowLayouts;
    QList<QList<QHBoxLayout*>*> tabColLayouts;
    QList<QList<GameFrame*>*> tabGameFrames;

    int tabSetupCount = 0;

    int gameFrameWidth = 0;
    int maxGameFramesPerRow = 0;
    QTimer* updateTimer;

    void resizeEvent(QResizeEvent *event);

    void adjustTabLayouts(bool forceAdjust = false);

    void addGamesTab(const QString& title, int tab);

private slots:

    void onUpdate();
};

#endif // LIBRARYWIDGET_H
