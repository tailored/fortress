#include "firewallwindow.h"
#include "ui_firewallwindow.h"

/**
 * @brief fireWallWindow::fireWallWindow
 * @param parent
 */
fireWallWindow::fireWallWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::fireWallWindow)
{
    ui->setupUi(this);
    this->fwrapper = new functionWrapper;
    this->firewallWebView = ui->fireWallWebView;
    this->firewallWebView->setContextMenuPolicy(Qt::NoContextMenu);
    fdl = new FileDownloader(QUrl::fromUserInput(FORTRESS_GITHUB_STASHLIST_URL), this);
    connect(fdl,SIGNAL(downloaded()),SLOT(setStashesList()));
    this->updateWebView();
}

/**
 * @brief fireWallWindow::~fireWallWindow
 */
fireWallWindow::~fireWallWindow()
{
    delete ui;
}

/**
 * @brief fireWallWindow::updateWebView
 */
void fireWallWindow::updateWebView() {
    this->firewallWebView->page()->mainFrame()->addToJavaScriptWindowObject("fwrapper",this->fwrapper);
    this->firewallWebView->page()->mainFrame()->addToJavaScriptWindowObject("smanager", SettingsManager::getSharedInstance());
}

/**
 * @brief fireWallWindow::on_fireWallWebView_loadFinished
 * @param arg1
 */
void fireWallWindow::on_fireWallWebView_loadFinished(bool arg1)
{
    if(arg1) this->updateWebView();
}

/**
 * @brief fireWallWindow::setStashesList
 */
void fireWallWindow::setStashesList() {
    SettingsManager::getSharedInstance()->setStashesList(fdl->downloadedData());
    this->updateWebView();
}
