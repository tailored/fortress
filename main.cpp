#include "firewallwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    fireWallWindow w;
    w.show();

    return a.exec();
}
