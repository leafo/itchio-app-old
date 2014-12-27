#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include "widgets/abstractview.h"
#include "ui_settingswidget.h"

namespace itchio {

class Settings;

//TODO Remove this when a proper SettingsController has been implemented.
class AppController;
using SettingsController = AppController;

class SettingsWidget : public AbstractView<Ui::SettingsWidget, SettingsController, Settings>
{
    Q_OBJECT

public:
    SettingsWidget(SettingsController& controller, QWidget* const parent);

private:
    QCheckBox* const autoLoginCheckBox_;
    QCheckBox* const autoUpdatesCheckBox_;
    QCheckBox* const trayNotificationsCheckBox_;

private slots:
    void refresh();
    void onAutoLoginChecked(const bool checked);
    void onAutoUpdatesChecked(const bool checked);
    void onTrayNotificationsChecked(const bool checked);
};

} // namespace itchio

#endif // SETTINGSWIDGET_H
