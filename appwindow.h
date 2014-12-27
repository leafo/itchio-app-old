#ifndef APPWINDOW_H
#define APPWINDOW_H

#include <QCloseEvent>
#include <QGridLayout>
#include <QMainWindow>
#include <QObject>
#include <QPoint>
#include <QSize>
#include <QSizeGrip>

namespace Ui
{
class AppWindow;
}

namespace itchio {

class AppController;
class LoginWidget;
class LibraryWidget;

class AppWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AppWindow(AppController& controller);
    ~AppWindow();

    inline AppController& controller(){ return controller_; }
    inline const AppController& const_controller() const { return controller_; }


    LoginWidget* loginWidget;
    LibraryWidget* libraryWidget;

    void setupSizeGrip();
    void setupLogin();
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
    AppController& controller_;

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

} // namespace itchio

#endif // APPWINDOW_H
