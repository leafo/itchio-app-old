#ifndef APPWINDOW_H
#define APPWINDOW_H

#include <QCloseEvent>
#include <QGridLayout>
#include <QMainWindow>
#include <QObject>
#include <QPoint>
#include <QSize>
#include <QSizeGrip>
#include <QDesktopWidget>
#include <QList>
#include <QPushButton>

#include "appcontroller.h"

class LoginWidget;
class LibraryWidget;

namespace Ui
{
class AppWindow;
}

class AppWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AppWindow(AppController* const controller, QWidget* const parent = 0);
    ~AppWindow();

    LoginWidget* loginWidget;
    LibraryWidget* libraryWidget;

    QString currentWidget;

    bool isMaximized;

    QDesktopWidget* desktop;

    QPoint oldPosition;
    QSize oldSize;

    void setupSizeGrip();
    void setupLibrary();

    void showWindow();
    void hideWindow();

private:
    void closeEvent(QCloseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

    void setStatus(QString status, bool disable);

    void maximize();
    void restore();

    Ui::AppWindow* const ui;
    AppController* const controller;

    QList<QWidget*> widgets;

    QObject* firstClicked;

    int dragClickX;
    int dragClickY;

    QSizeGrip* sizeGrip;
    QWidget* topBar;
    QGridLayout* appWindowLayout;
    QGridLayout* widgetsLayout;

    QList<QPushButton*> topBarWidgetButtons;

signals:

public slots:

private slots:
    void onScreenCountChange();
    void onDesktopResize();
    void onWidgetChange(QWidget* newWidget);

    void on_topBarCloseButton_clicked();
    void on_libraryButton_clicked();
};

#endif // APPWINDOW_H
