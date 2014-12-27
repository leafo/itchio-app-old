#include <QFile>

#include "appcontroller.h"

int main(int argc, char *argv[])
{
    itchio::AppController a(argc, argv);

    a.setOrganizationName("itch.io");
    a.setOrganizationDomain("itch.io");
    a.setApplicationName("itch.io");

    QFile styleFile(":/stylesheet.qss");
    if (styleFile.open(QIODevice::ReadOnly)) {
        QTextStream textStream(&styleFile);
        QString styleSheet = textStream.readAll();
        styleFile.close();
        a.setStyleSheet(styleSheet);
    }

    return a.exec();
}
