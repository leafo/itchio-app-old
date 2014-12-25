#include "settingswidget.h"
#include "ui_settingswidget.h"

#include <QtDebug>

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

    keepLoggedInBox->setChecked(controller->settings->loadSetting(KEEP_LOGGED_IN) == "1");
    automaticallyCheckForUpdatesBox->setChecked(controller->settings->loadSetting(AUTO_UPDATE_CHECK) == "1");
    showTrayNotificationsBox->setChecked(controller->settings->loadSetting(SHOW_TRAY_NOTIFICATION) == "1");
}

SettingsWidget::~SettingsWidget()
{
    delete ui;
}

void SettingsWidget::on_keepLoggedInBox_clicked()
{
    controller->settings->saveSetting(KEEP_LOGGED_IN,
                                      QString::number(keepLoggedInBox->isChecked()));
}

void SettingsWidget::on_automaticallyCheckForUpdatesBox_clicked()
{
    controller->settings->saveSetting(AUTO_UPDATE_CHECK,
                                      QString::number(automaticallyCheckForUpdatesBox->isChecked()));
}

void SettingsWidget::on_showTrayNotificationsBox_clicked()
{
    controller->settings->saveSetting(SHOW_TRAY_NOTIFICATION,
                                      QString::number(showTrayNotificationsBox->isChecked()));
}
