#ifndef SECONDARYWINDOW_H
#define SECONDARYWINDOW_H

#include <QDialog>
#include <QObject>
#include <QSize>
#include <QWidget>
#include <QCloseEvent>
#include <QGridLayout>

#include "appcontroller.h"

namespace Ui
{
class SecondaryWindow;
}

class SecondaryWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SecondaryWindow(QWidget* const widget, AppController* const controller, QWidget* const parent = 0);
    ~SecondaryWindow();

    QString name;

private:
    void closeEvent(QCloseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    void closeWindow();

    QObject* firstClicked;

    Ui::SecondaryWindow* const ui;
    AppController* const controller;
    QWidget* const widget;

    int dragClickX;
    int dragClickY;

    QWidget* topBar;
    QGridLayout* widgetsLayout;

signals:

public slots:

private slots:
    void on_topBarCloseButton_clicked();

};

#endif // SECONDARYWINDOW_H
