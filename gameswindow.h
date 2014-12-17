#ifndef GAMESWINDOW_H
#define GAMESWINDOW_H

#include <QMainWindow>
#include <QStringListModel>

#include "appcontroller.h"
#include "objects/game.h"

namespace Ui {
class GamesWindow;
}

class GamesWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GamesWindow(AppController* controller, QWidget *parent = 0);
    ~GamesWindow();

public slots:
    void onMyGames(QList<Game> games);

private slots:
    void on_actionQuit_triggered();

    void on_actionRefresh_triggered();

private:
    Ui::GamesWindow *ui;
    AppController* controller;

    void refreshGames();
};

#endif // GAMESWINDOW_H
