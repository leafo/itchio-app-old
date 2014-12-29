#include <QtDebug>

#include "settingswidget.h"
#include "ui_settingswidget.h"

//TODO: Thread settings setting process to avoid interface delay.

SettingsWidget::SettingsWidget(AppController *controller, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWidget),
    controller(controller)
{
    ui->setupUi(this);

    keepLoggedInBox = findChild<QCheckBox*>("keepLoggedInBox");
    automaticallyCheckForUpdatesBox = findChild<QCheckBox*>("automaticallyCheckForUpdatesBox");
    showTrayNotificationsBox = findChild<QCheckBox*>("showTrayNotificationsBox");

    refresh();
}

SettingsWidget::~SettingsWidget()
{
    delete ui;
}

void SettingsWidget::refresh()
{
    keepLoggedInBox->setChecked(controller->settings->autoLogin());
    automaticallyCheckForUpdatesBox->setChecked(controller->settings->autoUpdateChecks());
    showTrayNotificationsBox->setChecked(controller->settings->showTrayNotifications());
}

void SettingsWidget::on_keepLoggedInBox_clicked()
{
    controller->settings->enableAutoLogin(keepLoggedInBox->isChecked());
}

void SettingsWidget::on_automaticallyCheckForUpdatesBox_clicked()
{
    controller->settings->enableAutoUpdateChecks(automaticallyCheckForUpdatesBox->isChecked());
}

void SettingsWidget::on_showTrayNotificationsBox_clicked()
{
    controller->settings->enableTrayNotifications(showTrayNotificationsBox->isChecked());
}
