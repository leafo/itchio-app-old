#include "settingswidget.h"
#include "settings.h"
#include "appcontroller.h" // TODO Replace with settingscontroller.h

#include <QCheckBox>
#include <QtDebug>

using itchio::SettingsWidget;

//TODO: Thread settings setting process to avoid interface delay.

SettingsWidget::SettingsWidget(SettingsController& controller, QWidget* const parent) :
    AbstractView(controller, controller.settings(), parent),
    autoLoginCheckBox_(findChild<QCheckBox*>("keepLoggedInBox")),
    autoUpdatesCheckBox_(findChild<QCheckBox*>("automaticallyCheckForUpdatesBox")),
    trayNotificationsCheckBox_(findChild<QCheckBox*>("showTrayNotificationsBox"))
{
    connect(autoLoginCheckBox_,         &QCheckBox::clicked, this, &SettingsWidget::onAutoLoginChecked);
    connect(autoUpdatesCheckBox_,       &QCheckBox::clicked, this, &SettingsWidget::onAutoUpdatesChecked);
    connect(trayNotificationsCheckBox_, &QCheckBox::clicked, this, &SettingsWidget::onTrayNotificationsChecked);

    refresh();
}

void SettingsWidget::refresh()
{
    // The model_ is a reference to the current settings.
    autoLoginCheckBox_->setChecked(model_.autoLogin());
    autoUpdatesCheckBox_->setChecked(model_.autoUpdateChecks());
    trayNotificationsCheckBox_->setChecked(model_.showTrayNotifications());
}

void SettingsWidget::onAutoLoginChecked(const bool checked)
{
    model_.enableAutoLogin(checked);
}

void SettingsWidget::onAutoUpdatesChecked(const bool checked)
{
    model_.enableAutoUpdateChecks(checked);
}

void SettingsWidget::onTrayNotificationsChecked(const bool checked)
{
    model_.enableTrayNotifications(checked);
}

