#include "loginwidget.h"
#include "itchioapi.h"
#include "appcontroller.h" // TODO Replace with logincontroller.h

#include <QtDebug>

using itchio::LoginWidget;

LoginWidget::LoginWidget(LoginController& controller, QWidget* const parent) :
    AbstractView(controller, controller.api(), parent)
{
    // TODO Are these connections redundant?
    connect(&model_, &Api::onLogin,        this, &LoginWidget::onLogin);
    connect(&model_, &Api::onLoginFailure, this, &LoginWidget::onLoginFailure);

    connect(ui_->loginButton,        &QPushButton::clicked,     this, &LoginWidget::onLoginTentative);
    connect(ui_->loginUsernameInput, &QLineEdit::returnPressed, this, &LoginWidget::onLoginTentative);
    connect(ui_->loginPasswordInput, &QLineEdit::returnPressed, this, &LoginWidget::onLoginTentative);
}

void LoginWidget::setStatus(const QString& status, bool disable)
{
    ui_->loginStatusLabel->setText(status);
    ui_->loginUsernameInput->setDisabled(disable);
    ui_->loginPasswordInput->setDisabled(disable);
    ui_->loginButton->setDisabled(disable);
}

void LoginWidget::onLoginTentative()
{
    const auto& username = ui_->loginUsernameInput->text();
    const auto& password = ui_->loginPasswordInput->text();

    if (username == "" || password == "") {
        setStatus("Please enter username and password", false);
        return;
    }

    setStatus("Logging in...", true);
    model_.loginWithPassword(username, password);
}

void LoginWidget::onLoginFailure(const QString& error)
{
    setStatus(error, false);
}

void LoginWidget::onLogin()
{
    controller_.onLogin();
}
