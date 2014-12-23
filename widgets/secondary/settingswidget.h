#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QWidget>

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

private:
    Ui::SettingsWidget *ui;
    AppController* controller;

};

#endif // SETTINGSWIDGET_H
