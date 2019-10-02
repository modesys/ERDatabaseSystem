#include "../src/define.h"
#include "../ui/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName(APPNAME);
    a.setApplicationVersion(APPVER);
    a.setOrganizationName(ORGNAME);
    a.setStyle("fusion");
    MainWindow w;
    w.show();
    return a.exec();
}

