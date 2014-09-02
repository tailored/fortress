/**************************************************************************
 * Copyright (C) 2014  - Christian Richter                                *
 *                     - Daniel Niedermeyer                               *
 *                     - Benjamin Hiefner                                 *
 *                                                                        *
 * This program is free software: you can redistribute it and/or modify   *
 * it under the terms of the GNU General Public License as published by   *
 * the Free Software Foundation, either version 3 of the License, or      *
 * (at your option) any later version.                                    *
 *                                                                        *
 * This program is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 * GNU General Public License for more details.                           *
 *                                                                        *
 * You should have received a copy of the GNU General Public License      *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>   *
 **************************************************************************
 * File: firewallwindow.cpp                                               *
 **************************************************************************/

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
    this->ui->actionDeploy->setIcon(this->style()->standardIcon(QStyle::SP_DialogOkButton));
    this->ui->actionExport->setIcon(this->style()->standardIcon(QStyle::SP_DialogYesButton));
    this->ui->actionQuit->setIcon(this->style()->standardIcon(QStyle::SP_DialogCloseButton));
    this->ui->actionUpdateRemote->setIcon(this->style()->standardIcon(QStyle::SP_DriveNetIcon));
    this->ui->actionSave->setIcon(this->style()->standardIcon(QStyle::SP_DialogSaveButton));
    this->ui->actionClear->setIcon(this->style()->standardIcon(QStyle::SP_DialogResetButton));
    this->ui->actionSaveAs->setIcon(this->style()->standardIcon(QStyle::SP_DialogSaveButton));
    this->ui->actionDebploy_on_Boot->setIcon(this->style()->standardIcon(QStyle::SP_DialogApplyButton));
    this->ui->actionRemove_from_Boot->setIcon(this->style()->standardIcon(QStyle::SP_DialogDiscardButton));
    this->ui->mainToolBar->setFloatable(false);
    this->ui->mainToolBar->setMovable(false);
    // this is for debug remove!
    FortressGenerator::getSharedInstance();
    RulesManager::getSharedInstance();
    SettingsManager::getSharedInstance()->detectOS();
    this->osIsSupported();
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
            QFile tmpFile(SettingsManager::getSharedInstance()->getFullSettingsPath().append(FORTRESS_RULES_MANAGER_RULES_REL_PATH_USER_PRESETS).append(qi));
            if(tmpFile.exists()) {
                QMessageBox::StandardButton reply = QMessageBox::question(this,
                                                                          FORTRESS_RULESET_SAVE_OVERWRITE_WARNING_TITLE,
                                                                          FORTRESS_RULESET_SAVE_OVERWRITE_WARNING_TEXT,
                                                                          QMessageBox::Yes|QMessageBox::No);
                if(reply == QMessageBox::No) ok = false;
            }
            if( ok && !qi.isEmpty()) rn = qi;
        }
    } else {
        rn = RulesManager::getSharedInstance()->GetCurrentRulesetName();
    }
    rn = QRegExp::escape(rn);
    QString tmpPath = SettingsManager::getSharedInstance()->getFullSettingsPath().append(FORTRESS_RULES_MANAGER_RULES_REL_PATH_USER_PRESETS).append(rn);
    QFileInfo tmpFile = tmpPath;
    RulesManager::getSharedInstance()->SaveRule(tmpPath,r,true);
    RulesManager::getSharedInstance()->SetCurrentRulesetname(tmpFile.fileName());
    this->ui->fireWallWebView->page()->mainFrame()->evaluateJavaScript("setCurrentRulesetName()");
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
    QMessageBox::StandardButton qd;
    qd = QMessageBox::question(this,FORTRESS_DIALOG_TITLE_ARE_YOUR_SURE, FORTRESS_DIALOG_TEXT_DEPLOY_SYSTEM, QMessageBox::Yes|QMessageBox::No);
    if(qd == QMessageBox::Yes) {
        this->exportFileChoosen(QString::fromLatin1("/tmp/firewall.sh"));
        QProcess process;
        process.startDetached(SettingsManager::getSharedInstance()->getValue("settings/sudoprovider"), QStringList() << "/tmp/firewall.sh");
    }
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
        this->ui->fireWallWebView->page()->mainFrame()->evaluateJavaScript("setCurrentRulesetName()");
        this->ui->fireWallWebView->page()->mainFrame()->evaluateJavaScript("callbackClearRules()");
    }


}

/**
 * @brief fireWallWindow::on_actionQuit_triggered
 */
void fireWallWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

/**
 * @brief fireWallWindow::on_actionSaveAs_triggered
 */
void fireWallWindow::on_actionSaveAs_triggered()
{
    QString rn = NULL;
    QString tmpRn = RulesManager::getSharedInstance()->GetCurrentRulesetName();
    QString r = this->getCurrentConfig();
    while(rn == NULL) {
        bool ok = false;
        QString qi = QInputDialog::getText(this, FORTRESS_RULESET_SAVE_DIALOG_TITLE, FORTRESS_RULESET_SAVE_DIALOG_TEXT,QLineEdit::Normal,QString::null,&ok);
        if(!ok) return;
        QFile tmpFile(SettingsManager::getSharedInstance()->getFullSettingsPath().append(FORTRESS_RULES_MANAGER_RULES_REL_PATH_USER_PRESETS).append(qi));
        if(tmpFile.exists()) {
            QMessageBox::StandardButton reply = QMessageBox::question(this,
                                                                      FORTRESS_RULESET_SAVE_OVERWRITE_WARNING_TITLE,
                                                                      FORTRESS_RULESET_SAVE_OVERWRITE_WARNING_TEXT,
                                                                      QMessageBox::Yes|QMessageBox::No);
            if(reply == QMessageBox::No) ok = false;
        }
        if( ok && !qi.isEmpty() ) rn = qi;
    }
    rn = QRegExp::escape(rn);
    QString tmpPath = SettingsManager::getSharedInstance()->getFullSettingsPath().append(FORTRESS_RULES_MANAGER_RULES_REL_PATH_USER_PRESETS).append(rn);
    QFileInfo tmpFile = tmpPath;
    RulesManager::getSharedInstance()->SaveRule(tmpPath,r,true);
    RulesManager::getSharedInstance()->SetCurrentRulesetname(tmpFile.fileName());
    this->ui->fireWallWebView->page()->mainFrame()->evaluateJavaScript("setCurrentRulesetName()");
}

/**
 * @brief fireWallWindow::on_actionDebploy_on_Boot_triggered
 */
void fireWallWindow::on_actionDebploy_on_Boot_triggered()
{
    QMessageBox::StandardButton qd;
    qd = QMessageBox::question(this,FORTRESS_DIALOG_TITLE_ARE_YOUR_SURE,FORTRESS_DIALOG_TEXT_DEPLOY_SYSTEM_BOOT, QMessageBox::Yes|QMessageBox::No);
    if(qd == QMessageBox::Yes) {
        SettingsManager::getSharedInstance()->detectOS();

        if(this->osIsSupported()) {
            QDir qDir(FORTRESS_RULES_BOOT_DEPLOYMENT_PATH);
            if(!qDir.exists()) {
                QProcess process;
                process.execute(SettingsManager::getSharedInstance()->getValue("settings/sudoprovider"),
                                      QStringList() << QString::fromLatin1("mkdir -p -m a+rwx ").append(FORTRESS_RULES_BOOT_DEPLOYMENT_PATH));
            }
            this->exportFileChoosen(QString::fromLatin1(FORTRESS_RULES_BOOT_DEPLOYMENT_PATH).append("firewall.sh"));
            QString os = SettingsManager::getSharedInstance()->getValue("settings/os");
            if(os.compare("Gentoo") == 0) {
                OsDeploymentHelper::gentooDeploy();
            } else if(os.compare("Ubuntu") == 0
                      || os.compare("Debian") == 0
                      || os.compare("Fedora") == 0) {
                OsDeploymentHelper::ubuntuDeploy();
            }
        }
    }
}

/**
 * @brief fireWallWindow::osIsSupported
 * @return
 */
bool fireWallWindow::osIsSupported() {
    if(SettingsManager::getSharedInstance()->getValue("settings/os_supported").compare("true") != 0) {
        QMessageBox::critical(this,FORTRESS_DIALOG_TITLE_CRITICAL_ERROR,FORTRESS_DIALOG_TEXT_OS_UNSUPPORTED,QMessageBox::Ok);
        this->ui->actionDeploy->setEnabled(false);
        this->ui->actionDebploy_on_Boot->setEnabled(false);
        return false;
    } else {
        this->ui->actionDeploy->setEnabled(true);
        this->ui->actionDebploy_on_Boot->setEnabled(true);
        return true;
    }
}

/**
 * @brief fireWallWindow::on_actionRemove_from_Boot_triggered
 */
void fireWallWindow::on_actionRemove_from_Boot_triggered()
{
    QMessageBox::StandardButton qm = QMessageBox::critical(this,FORTRESS_DIALOG_TITLE_ARE_YOUR_SURE,FORTRESS_DIALOG_TEXT_DROP_FROM_BOOT, QMessageBox::Yes|QMessageBox::No);
    if(qm == QMessageBox::Yes) {
        QString os = SettingsManager::getSharedInstance()->getValue("settings/os");
        if(os.compare("Gentoo") == 0) {
            OsDeploymentHelper::gentooRemove();
        } else if(os.compare("Ubuntu") == 0
                  || os.compare("Debian") == 0
                  || os.compare("Fedora") == 0) {
            OsDeploymentHelper::ubuntuRemove();
        }
        qm = QMessageBox::critical(this,FORTRESS_DIALOG_TITLE_REBOOT, FORTRESS_DIALOG_TEXT_REBOOT,QMessageBox::Yes|QMessageBox::No);
        if(qm == QMessageBox::Yes) {
            QProcess process;
            process.execute(SettingsManager::getSharedInstance()->getValue("settings/os_supported"),QStringList() << QString::fromLatin1("reboot"));
        }
    }
}
