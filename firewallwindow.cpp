#include "firewallwindow.h"
#include "ui_firewallwindow.h"

// TODO: IMPLEMENT SAVE AS FUNCTION!

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
    this->ui->actionDeploy->setIcon(this->style()->standardIcon(QStyle::SP_DialogOkButton));
    this->ui->actionExport->setIcon(this->style()->standardIcon(QStyle::SP_DialogYesButton));
    this->ui->actionQuit->setIcon(this->style()->standardIcon(QStyle::SP_DialogCloseButton));
    this->ui->actionUpdateRemote->setIcon(this->style()->standardIcon(QStyle::SP_DriveNetIcon));
    this->ui->actionSave->setIcon(this->style()->standardIcon(QStyle::SP_DialogSaveButton));
    this->ui->actionClear->setIcon(this->style()->standardIcon(QStyle::SP_DialogDiscardButton));
    this->ui->mainToolBar->setFloatable(false);
    this->ui->mainToolBar->setMovable(false);
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
    this->ui->fireWallWebView->page()->mainFrame()->addToJavaScriptWindowObject("rmanager", RulesManager::getSharedInstance());
    this->ui->fireWallWebView->page()->mainFrame()->addToJavaScriptWindowObject("mwindow", this);
    this->ui->fireWallWebView->page()->mainFrame()->evaluateJavaScript("setCurrentRulesetName()");
    this->updateStashesContent();
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
 * @brief fireWallWindow::updateStashesContent
 */
void fireWallWindow::updateStashesContent() {
    QFileInfo tmp(SettingsManager::getSharedInstance()->getValue("settings/stashurl"));
    rDl = new FileDownloader(tmp.path().append('/').append(FORTRESS_STASHES_RULES_FILENAME));
    connect(rDl,SIGNAL(downloaded()),SLOT(setRulesList()));
    pDl = new FileDownloader(tmp.path().append('/').append(FORTRESS_STASHES_PRESETS_FILENAME));
    connect(pDl,SIGNAL(downloaded()),SLOT(setPresetsList()));
}

/**
 * @brief fireWallWindow::setRulesList
 */
void fireWallWindow::setRulesList() {
    RulesManager::getSharedInstance()->SaveRulesFromStash(this->rDl->downloadedData());
    this->ui->fireWallWebView->page()->mainFrame()->evaluateJavaScript("callBackUpdateRules()");
    this->rulesDone = true;
    this->updateFinished();
}

/**
 * @brief fireWallWindow::setPresetsList
 */
void fireWallWindow::setPresetsList() {
    RulesManager::getSharedInstance()->SavePresetsFromStash(this->pDl->downloadedData());
    this->ui->fireWallWebView->page()->mainFrame()->evaluateJavaScript("callBackUpdatePresets()");
    this->presetsDone = true;
    this->updateFinished();
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

/**
 * @brief fireWallWindow::on_actionExport_triggered
 */
void fireWallWindow::on_actionExport_triggered()
{
    QFileDialog *qf = new QFileDialog(this, FORTRESS_DIALOG_EXPORT, getenv("HOME"),tr("Shell-Script (*.sh)"));
    qf->setWindowModality(Qt::WindowModal);
    qf->setAcceptMode(QFileDialog::AcceptSave);
    qf->show();
    connect(qf,SIGNAL(fileSelected(QString)),this,SLOT(exportFileChoosen(QString)));
}

/**
 * @brief fireWallWindow::exportFileChoosen
 * @param fn
 */
void fireWallWindow::exportFileChoosen(QString fn) {
    // if extension missing add .sh
    QRegExp rx(".sh$");
    if(rx.indexIn(fn) < 0) fn.append(".sh");
    if(!FortressGenerator::getSharedInstance()->exportFirewallScript(fn, this->getCurrentConfig())) {
        QMessageBox *mb = new QMessageBox();
        mb->setText("Fortress failed to export the firewallscript!");
        mb->setIcon(QMessageBox::Warning);
        mb->show();
    }
}

/**
 * @brief fireWallWindow::on_actionUpdateRemote_triggered
 */
void fireWallWindow::on_actionUpdateRemote_triggered()
{
    this->ui->actionUpdateRemote->setDisabled(true);
    this->rulesDone = false;
    this->presetsDone = false;
    this->updateStashesContent();
}

/**
 * @brief fireWallWindow::updateFinished
 */
void fireWallWindow::updateFinished() {
    if(this->rulesDone && this->presetsDone) {
        this->ui->actionUpdateRemote->setEnabled(true);
        this->ui->actionUpdateRemote->setEnabled(true);
    }
}

/**
 * @brief fireWallWindow::on_actionSave_triggered
 */
void fireWallWindow::on_actionSave_triggered()
{
    QString rn = NULL;
    QString tmpRn = RulesManager::getSharedInstance()->GetCurrentRulesetName();
    QString r = this->getCurrentConfig();
    if(
            tmpRn.compare(FORTRESS_DEFAULT_RULESET_NAME) == 0
            || tmpRn.isEmpty()
      ) {
        while(rn == NULL) {
            bool ok = false;
            QString qi = QInputDialog::getText(this, FORTRESS_RULESET_SAVE_DIALOG_TITLE, FORTRESS_RULESET_SAVE_DIALOG_TEXT,QLineEdit::Normal,QString::null,&ok);
            if(!ok) return;
            if( ok && !qi.isEmpty() ) rn = qi;
        }
    } else {
        rn = RulesManager::getSharedInstance()->GetCurrentRulesetName();
    }
    QString tmpPath = SettingsManager::getSharedInstance()->getFullSettingsPath().append(FORTRESS_RULES_MANAGER_RULES_REL_PATH_USER_PRESETS).append(rn);
    QFileInfo tmpFile = tmpPath;
    RulesManager::getSharedInstance()->SaveRule(tmpPath,r,true);
    RulesManager::getSharedInstance()->SetCurrentRulesetname(tmpFile.fileName());
    this->ui->fireWallWebView->page()->mainFrame()->evaluateJavaScript("setRuleName()");
}


/**
 * @brief fireWallWindow::getCurrentConfig
 */
QString fireWallWindow::getCurrentConfig() {
    return this->ui->fireWallWebView->page()->mainFrame()->evaluateJavaScript("getCurrentRules()").toString();
}

/**
 * @brief fireWallWindow::on_actionDeploy_triggered
 */
void fireWallWindow::on_actionDeploy_triggered()
{
    // TODO: run this file on the current system and make it persistant on boot
    // TODO: add deploy logic for debian/ubuntu
    this->exportFileChoosen(QString::fromLatin1("/tmp/tmp.sh"));
}

/**
 * @brief fireWallWindow::on_actionClear_triggered
 */
void fireWallWindow::on_actionClear_triggered()
{
    QMessageBox *qm = new QMessageBox(this);
    qm->setText(FORTRESS_RULESET_CLEAR_TEXT);
    qm->setWindowTitle(FORTRESS_RULESET_CLEAR_TITLE);
    qm->setIcon(QMessageBox::Warning);
    qm->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    qm->setDefaultButton(QMessageBox::Cancel);
    int ret = qm->exec();
    if(ret == QMessageBox::Ok) {
        RulesManager::getSharedInstance()->SetCurrentRulesetname(FORTRESS_DEFAULT_RULESET_NAME);
        this->ui->fireWallWebView->page()->mainFrame()->evaluateJavaScript("setRuleName()");
    }


}

void fireWallWindow::on_actionQuit_triggered()
{

}
