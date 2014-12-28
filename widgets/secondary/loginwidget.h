#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>

#include "appcontroller.h"
#include "appsettings.h"

namespace Ui
{
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget* const parent, AppController* const controller);
    ~LoginWidget();

private:
    Ui::LoginWidget* const ui;
    AppController* const controller;

    void setStatus(const QString& status, bool disable);

private slots:
    void onLoginTentative();
    void onLoginFailure(QString error);

    void on_loginButton_clicked();
    void on_loginUsernameInput_returnPressed();
    void on_loginPasswordInput_returnPressed();
};

#endif // LOGINWIDGET_H
