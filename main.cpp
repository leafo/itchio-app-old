#include <QApplication>
#include <QFile>

#include "appcontroller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile styleFile(":/stylesheet.qss");
    if(styleFile.open(QIODevice::ReadOnly))
    {
        QTextStream textStream(&styleFile);
        QString styleSheet = textStream.readAll();
        styleFile.close();
        a.setStyleSheet(styleSheet);
    }
    AppController controller;
    return a.exec();
}
