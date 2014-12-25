#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QWidget>
#include <QCheckBox>

#include "appcontroller.h"
#include "appsettings.h"

namespace Ui {
class SettingsWidget;
}

class SettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWidget(AppController* controller, QWidget *parent = 0);
    ~SettingsWidget();

private slots:
    void on_keepLoggedInBox_clicked();

    void on_automaticallyCheckForUpdatesBox_clicked();

    void on_showTrayNotificationsBox_clicked();

private:
    Ui::SettingsWidget *ui;
    AppController* controller;

    QCheckBox* keepLoggedInBox;
    QCheckBox* automaticallyCheckForUpdatesBox;
    QCheckBox* showTrayNotificationsBox;
};

#endif // SETTINGSWIDGET_H
