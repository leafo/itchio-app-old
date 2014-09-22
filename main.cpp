#include <QApplication>

#include "appcontroller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AppController controller;
    return a.exec();
}
