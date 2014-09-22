#ifndef GAMESWINDOW_H
#define GAMESWINDOW_H

#include <QMainWindow>

namespace Ui {
class GamesWindow;
}

class GamesWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GamesWindow(QWidget *parent = 0);
    ~GamesWindow();

private:
    Ui::GamesWindow *ui;
};

#endif // GAMESWINDOW_H
