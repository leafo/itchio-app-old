#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "itchioapi.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::LoginDialog* ui;
    ItchioApi* api;

};

#endif // LOGINDIALOG_H
