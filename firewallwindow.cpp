#include "firewallwindow.h"
#include "ui_firewallwindow.h"

fireWallWindow::fireWallWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::fireWallWindow)
{
    ui->setupUi(this);
    this->fwrapper = new functionWrapper;
    this->firewallWebView = ui->fireWallWebView;
    this->updateWebView();
}

fireWallWindow::~fireWallWindow()
{
    delete ui;
}

void fireWallWindow::updateWebView() {
    qDebug("webView: adding javascript wrapper");
    this->firewallWebView->page()->mainFrame()->addToJavaScriptWindowObject("fwrapper",this->fwrapper);
}


void fireWallWindow::on_fireWallWebView_loadFinished(bool arg1)
{
    qDebug("webView: load completed");
    this->updateWebView();
}
