#include "firewallwindow.h"
#include "ui_firewallwindow.h"

fireWallWindow::fireWallWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::fireWallWindow)
{
    QCoreApplication::setOrganizationName(FORTRESS_ORGANISATION);
    QCoreApplication::setOrganizationDomain(FORTRESS_ORGANISATION_DOMAIN);
    QCoreApplication::setApplicationName(FORTRESS_APPLICATION);
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
    this->firewallWebView->page()->mainFrame()->addToJavaScriptWindowObject("smanager", SettingsManager::getSharedInstance());
}


void fireWallWindow::on_fireWallWebView_loadFinished(bool arg1)
{
    qDebug("webView: load completed");
    this->updateWebView();
}
