#ifndef APPWINDOW_H
#define APPWINDOW_H

#include <QCloseEvent>
#include <QGridLayout>
#include <QMainWindow>
#include <QObject>
#include <QPoint>
#include <QSize>
#include <QSizeGrip>

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

    void setupSizeGrip();
    void setupLibrary();

    QString currentWidget;

    QPoint oldPosition;

private:
    void closeEvent(QCloseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

    void setStatus(QString status, bool disable);

    void close();
    void maximize();
    void restore();

    Ui::AppWindow* const ui;
    AppController* const controller;

    QObject* firstClicked;

    QSize oldSize;
    int dragClickX;
    int dragClickY;

    QSizeGrip* sizeGrip;
    QWidget* topBar;
    QGridLayout* appWindowLayout;
    QGridLayout* widgetsLayout;

signals:

public slots:

private slots:
    void onWidgetChange(QWidget* newWidget);
    void on_topBarCloseButton_clicked();

};

#endif // APPWINDOW_H
