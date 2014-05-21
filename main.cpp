#include "firewallwindow.h"
#include <QApplication>

/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    fireWallWindow w;
    w.show();

    return a.exec();
}
