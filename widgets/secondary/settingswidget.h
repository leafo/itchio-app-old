#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QWidget>
#include <QCheckBox>

#include "appcontroller.h"
#include "appsettings.h"

namespace Ui
{
class SettingsWidget;
}

class SettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWidget(AppController* const controller, QWidget* const parent = 0);
    ~SettingsWidget();

private slots:
    void refresh();

    void on_keepLoggedInBox_clicked();

    void on_automaticallyCheckForUpdatesBox_clicked();

    void on_showTrayNotificationsBox_clicked();

    void on_showDownloadFinishedNotificationsBox_clicked();

    void on_showLibraryUpdateNotificationsBox_clicked();

    void on_showGameUpdateAvailableNotificationsBox_clicked();

private:
    Ui::SettingsWidget* const ui;
    AppController* const controller;
};

#endif // SETTINGSWIDGET_H
