#include <QtDebug>

#include "settingswidget.h"
#include "ui_settingswidget.h"

//TODO: Thread settings setting process to avoid interface delay.

SettingsWidget::SettingsWidget(AppController* controller, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::SettingsWidget)
    , controller(controller)
{
    ui->setupUi(this);

    refresh();
}

SettingsWidget::~SettingsWidget()
{
    delete ui;
}

void SettingsWidget::refresh()
{
    ui->keepLoggedInBox->setChecked(controller->settings->autoLogin());
    ui->automaticallyCheckForUpdatesBox->setChecked(controller->settings->autoUpdateChecks());
    ui->showTrayNotificationsBox->setChecked(controller->settings->showTrayNotifications());
}

void SettingsWidget::on_keepLoggedInBox_clicked()
{
    controller->settings->enableAutoLogin(ui->keepLoggedInBox->isChecked());
}

void SettingsWidget::on_automaticallyCheckForUpdatesBox_clicked()
{
    controller->settings->enableAutoUpdateChecks(ui->automaticallyCheckForUpdatesBox->isChecked());
}

void SettingsWidget::on_showTrayNotificationsBox_clicked()
{
    controller->settings->enableTrayNotifications(ui->showTrayNotificationsBox->isChecked());
}
