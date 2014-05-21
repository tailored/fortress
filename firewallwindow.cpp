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
    // disable context menus
    this->ui->fireWallWebView->setContextMenuPolicy(Qt::NoContextMenu);
    // download stashes list
    fdl = new FileDownloader(QUrl::fromUserInput(FORTRESS_GITHUB_STASHLIST_URL), this);
    connect(fdl,SIGNAL(downloaded()),SLOT(setStashesList()));
    // init the webview
    this->updateWebView();
    // some gfx stuff
    this->ui->actionDeploy->setIcon(this->style()->standardIcon(QStyle::SP_DesktopIcon));
    this->ui->actionExport->setIcon(this->style()->standardIcon(QStyle::SP_ComputerIcon));
    this->ui->actionQuit->setIcon(this->style()->standardIcon(QStyle::SP_DirClosedIcon));
    this->ui->mainToolBar->setFloatable(FALSE);
    this->ui->mainToolBar->setMovable(FALSE);

    // this is for debug remove!
    FortressGenerator::getSharedInstance();
    RulesManager::getSharedInstance();
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
    this->ui->fireWallWebView->page()->mainFrame()->addToJavaScriptWindowObject("smanager", SettingsManager::getSharedInstance());
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

/**
 * @brief fireWallWindow::resizeEvent
 * @param event
 */
void fireWallWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);
    QSize tmpSize = event->size();
    tmpSize.setHeight(tmpSize.height()-(this->ui->mainToolBar->height() + this->ui->menuBar->height()));
    this->ui->fireWallWebView->resize(tmpSize);
}
