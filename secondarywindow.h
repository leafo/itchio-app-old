#ifndef SECONDARYWINDOW_H
#define SECONDARYWINDOW_H

#include <QDialog>
#include <QObject>
#include <QSize>
#include <QWidget>
#include <QCloseEvent>
#include <QGridLayout>

namespace Ui
{
class SecondaryWindow;
}

namespace itchio {

class AppWindow;
class AppController;
class SettingsWidget;

class SecondaryWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SecondaryWindow(AppWindow& mainWindow);
    ~SecondaryWindow();

    QString name;

private:
    void closeEvent(QCloseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    void closeWindow();

    QObject* firstClicked;

    //FIXME Memory leak. Use smart pointer.
    Ui::SecondaryWindow* const ui;
    AppController& controller;
    SettingsWidget* const settingsWidget;

    QSize newWidgetSizeDiference;

    int dragClickX;
    int dragClickY;

    QWidget* topBar;
    QGridLayout* widgetsLayout;

signals:

public slots:

private slots:
    void on_topBarCloseButton_clicked();

};

} // namespace itchio

#endif // SECONDARYWINDOW_H
