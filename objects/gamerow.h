#ifndef GAMEROW_H
#define GAMEROW_H

#include <QWidget>

namespace Ui {
class GameRow;
}

class GameRow : public QWidget
{
    Q_OBJECT

public:
    explicit GameRow(QWidget *parent = 0);
    ~GameRow();

private:
    Ui::GameRow *ui;
};

#endif // GAMEROW_H
