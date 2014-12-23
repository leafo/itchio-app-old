#ifndef LIBRARYWIDGET_H
#define LIBRARYWIDGET_H

#include <QWidget>

#include "appcontroller.h"

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

private:
    Ui::LibraryWidget *ui;
    AppController* controller;
};

#endif // LIBRARYWIDGET_H
