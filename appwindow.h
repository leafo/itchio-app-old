#ifndef APPWINDOW_H
#define APPWINDOW_H

#include <QSizeGrip>
#include <QGridLayout>
#include <QMainWindow>
#include <QObject>
#include <QSize>
#include <QPoint>
#include <QCloseEvent>

#include "appcontroller.h"

namespace Ui
{
    class AppWindow;
}

class AppWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AppWindow(AppController* controller, QWidget* parent = 0);
    ~AppWindow();

private:
    void closeEvent(QCloseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

    int leftClickX;
    int leftClickY;
    QObject* firstClicked = NULL;

    QSize oldSize;
    QPoint oldPosition;

    Ui::AppWindow* ui;
    AppController* controller;

    QWidget* topBar;
    QGridLayout* appWindowLayout;

    void setStatus(QString status, bool disable);

private slots:
    void on_topBarCloseButton_clicked();

};

#endif // APPWINDOW_H
