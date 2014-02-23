#include "firewallwindow.h"
#include "ui_firewallwindow.h"

fireWallWindow::fireWallWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::fireWallWindow)
{
    ui->setupUi(this);
}

fireWallWindow::~fireWallWindow()
{
    delete ui;
}

