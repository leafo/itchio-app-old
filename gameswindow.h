#ifndef GAMESWINDOW_H
#define GAMESWINDOW_H

#include <QMainWindow>
#include "appcontroller.h"

namespace Ui {
class GamesWindow;
}

class GamesWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GamesWindow(AppController* controller, QWidget *parent = 0);
    ~GamesWindow();

private:
    Ui::GamesWindow *ui;
    AppController* controller;
};

#endif // GAMESWINDOW_H
