#include "rulesmanager.h"
/**
 * @brief rulesMangerInstance
 */
static RulesManager* rulesMangerInstance = NULL;


/**
 * @brief RulesManager::RulesManager
 * @param parent
 */
RulesManager::RulesManager(QObject *parent) :
    QObject(parent)
{
    this->configBasePath = SettingsManager::getSharedInstance()->getFullSettingsPath();
    this->fullRulePath = SettingsManager::getSharedInstance()->getFullSettingsPath()
            + FORTRESS_RULES_MANAGER_RULES_REL_PATH;
    this->userPresetPath = SettingsManager::getSharedInstance()->getFullSettingsPath()
            + FORTRESS_RULES_MANAGER_RULES_REL_PATH_USER_PRESETS;
    this->CheckDirs();
    QString tmpDefaultRulesetName = SettingsManager::getSharedInstance()->getValue("settings/activeRules");
    if(!tmpDefaultRulesetName.isEmpty())
        this->SetCurrentRulesetname(tmpDefaultRulesetName);
    else
        this->SetCurrentRulesetname(FORTRESS_DEFAULT_RULESET_NAME);
}

/**
 * @brief RulesManager::getSharedInstance
 * @return
 */
RulesManager* RulesManager::getSharedInstance() {
    if(rulesMangerInstance == NULL) rulesMangerInstance = new RulesManager();
    return rulesMangerInstance;
}

/**
 * @brief RulesManager::SaveRule
 * @param rule
 * @return
 */
int RulesManager::SaveRule(QString path, QString rule, bool overwrite) {
    QFileInfo tmpFileInfo(path);
    if(!overwrite && tmpFileInfo.exists()) return FORTRESS_RULES_MANAGER_SAVE_RULE_EXISTS;
        QFile tmpFile(path);
        if(tmpFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&tmpFile);
            out << rule;
            tmpFile.close();
            return FORTRESS_RULES_MANAGER_SAVE_OK;
        } else return FORTRESS_RULES_MANAGER_SAVE_RULE_ACCESS_DENIED;
}

/**
 * @brief RulesManager::SaveRulesFromStash
 * @param rules
 * @return
 */
int RulesManager::SaveRulesFromStash(QString rules) {
    QString tmp;
    tmp.append(this->fullRulePath);
    tmp.append(FORTRESS_STASHES_RULES_FILENAME);
    return this->SaveRule(tmp, rules, true);
}

/**
 * @brief RulesManager::SavePresetsFromStash
 * @param presets
 * @return
 */
int RulesManager::SavePresetsFromStash(QString presets) {
    QString tmp;
    tmp.append(this->fullRulePath);
    tmp.append(FORTRESS_STASHES_PRESETS_FILENAME);
    return this->SaveRule(tmp, presets, true);
}

/**
 * @brief RulesManager::LoadRule
 * @param rule
 * @return
 */
QString RulesManager::LoadRule(QString rulePath) {
    QFile rule(rulePath);
    if(rule.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QByteArray dump = rule.readAll();
        return dump;
    }
    return NULL;
}

/**
 * @brief RulesManager::LoadStashRules
 * @return
 */
QString RulesManager::LoadStashRules() {
    QString tmp(this->fullRulePath);
    return this->LoadRule(tmp.append(FORTRESS_STASHES_RULES_FILENAME));
}

/**
 * @brief RulesManager::LoadStashPresets
 * @return
 */
QString RulesManager::LoadStashPresets() {
    QString tmp(this->fullRulePath);
    return this->LoadRule(tmp.append(FORTRESS_STASHES_PRESETS_FILENAME));
}

/**
 * @brief RulesManager::LoadUserRules
 * @return
 */
QString RulesManager::LoadUserRules() {
    QDir rulesDir(SettingsManager::getSharedInstance()->getFullSettingsPath().append(FORTRESS_RULES_MANAGER_RULES_REL_PATH_USER_PRESETS));
    QStringList files = rulesDir.entryList(QDir::NoDotAndDotDot | QDir::Files, QDir::DirsFirst);
    QString retVal = "{ \"rulesets\": [";
    for(QStringList::Iterator it = files.begin(); it!=files.end();++it) {
        QString file = *it;
        QFile tmpFile(rulesDir.path().append('/').append(file));
        if(tmpFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            retVal.append("{\"name\":\"").append(tmpFile.fileName().section("/",-1,-1)).append("\", \"rules\":");
            retVal.append(tmpFile.readAll());
            retVal.append("},");
        }
    }
    // remove last comma if list is not empty
    if(retVal.at(retVal.length()-1) == ',') {
        retVal = retVal.remove(retVal.length()-1,1);
    }
    retVal.append("]}");
    return retVal;
}

/**
 * @brief RulesManager::ClearStashPresets
 * @return
 */
int RulesManager::ClearStashPresets() {
    QFileInfo tmp(this->stashesPresetPath);
    if(!tmp.exists()) return FORTRESS_RULES_MANAGER_SAVE_RULE_DOES_NOT_EXIST;
    else {
        QDir tmpDir(this->stashesPresetPath);
        tmpDir.setFilter( QDir::NoDotAndDotDot | QDir::Files );
        foreach( QString dirItem, tmpDir.entryList() )
            tmpDir.remove(dirItem);
        return FORTRESS_RULES_MANAGER_SAVE_OK;
    }
}

/**
 * @brief RulesManager::checkDirs
 */
void RulesManager::CheckDirs() {
    QStringList paths;
    paths << this->fullRulePath << this->userPresetPath;
    for(int i = 0; i < paths.size(); ++i) {
        QFileInfo tmp(paths.at(i));
        if(!tmp.exists() || !tmp.isDir()) {
            QProcess tmpProcess;
            tmpProcess.start("mkdir -p " + paths.at(i));
            tmpProcess.waitForFinished(10);
        }
    }
}

/**
 * @brief RulesManager::GenerateUUID
 * @return
 */
QString RulesManager::GenerateUUID() {
    return QUuid::createUuid().toString().replace("{","").replace("}","");
}

/**
 * @brief RulesManager::GetCurrentRulesetName
 * @return
 */
QString RulesManager::GetCurrentRulesetName() {
    return this->currentRulesetName;
}

/**
 * @brief RulesManager::SetCurrentRulesetname
 * @param n
 */
void RulesManager::SetCurrentRulesetname(QString n) {
    this->currentRulesetName = n;
    SettingsManager::getSharedInstance()->setValue("settings/activeRules", n);
}

/**
 * @brief RulesManager::GetFullRulePath
 * @return
 */
QString RulesManager::GetFullRulePath() {
    return this->fullRulePath;
}

/**
 * @brief RulesManager::DeleteUserRuleResponsive
 */
bool RulesManager::DeleteUserRuleResponsive(QString rule) {
    QMessageBox::StandardButton qd;
    qd = QMessageBox::question(NULL,FORTRESS_DIALOG_TITLE_ARE_YOUR_SURE,QString(FORTRESS_DIALOG_TEXT_DELETE_RULE_PART1).append(rule).append(FORTRESS_DIALOG_TEXT_DELETE_RULE_PART2), QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
    if(qd == QMessageBox::Yes) {
        if(QFile::remove(SettingsManager::getSharedInstance()->getFullSettingsPath().append(FORTRESS_RULES_MANAGER_RULES_REL_PATH_USER_PRESETS).append(rule)))  {
            return true;
        }
    } else return false;
    return false;
}

/**
 * @brief RulesManager::DeleteUserRule
 */
bool RulesManager::DeleteUserRule(QString rule) {
    if(QFile::remove(SettingsManager::getSharedInstance()->getFullSettingsPath().append(FORTRESS_RULES_MANAGER_RULES_REL_PATH_USER_PRESETS).append(rule))) return true;
    else return false;
}
