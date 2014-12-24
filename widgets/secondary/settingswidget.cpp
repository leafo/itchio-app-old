#include "settingswidget.h"
#include "ui_settingswidget.h"

#include <QtDebug>

SettingsWidget::SettingsWidget(AppController *controller, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWidget),
    controller(controller)
{
    ui->setupUi(this);
}

SettingsWidget::~SettingsWidget()
{
    delete ui;
}
