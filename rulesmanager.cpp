#include "rulesmanager.h"

static RulesManager* rulesMangerInstance = NULL;


/**
 * @brief RulesManager::RulesManager
 * @param parent
 */
RulesManager::RulesManager(QObject *parent) :
    QObject(parent)
{
    this->configBasePath = SettingsManager::getSharedInstance()->getFullSettingsPath();
    this->fullRulePath = SettingsManager::getSharedInstance()->getFullSettingsPath() + FORTRESS_RULES_MANAGER_RULES_REL_PATH;
    this->userPresetPath = SettingsManager::getSharedInstance()->getFullSettingsPath() + FORTRESS_RULES_MANAGER_RULES_REL_PATH_USER_PRESETS;
    this->stashesPresetPath = SettingsManager::getSharedInstance()->getFullSettingsPath() + FORTRESS_RULES_MANAGER_RULES_REL_PATH_STASHES_DATA;
    this->checkDirs();
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
 * @brief RulesManager::GenarateScriptFromRule
 * @param rule
 * @return
 */
QString RulesManager::GenarateScriptFromRule(QString rule) {
    return NULL;
}

/**
 * @brief RulesManager::LoadRule
 * @param rule
 * @return
 */
QString RulesManager::LoadRule(QString rule) {
    return NULL;
}

/**
 * @brief RulesManager::SaveRule
 * @param rule
 * @return
 */
int RulesManager::SaveRule(QString path, QString rule) {
    QFileInfo tmpFileInfo(path);
    if(tmpFileInfo.exists()) return FORTRESS_RULES_MANAGER_SAVE_RULE_EXISTS;
    QFile tmpFile(path);
    if(tmpFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&tmpFile);
        out << rule;
        return FORTRESS_RULES_MANAGER_SAVE_OK;
    } else return FORTRESS_RULES_MANAGER_SAVE_RULE_ACCESS_DENIED;

}

/**
 * @brief RulesManager::SaveUserPreset
 * @param rule
 * @return
 */
int RulesManager::SaveUserPreset(QString ruleName, QString rule) {
    QString tmp;
    tmp.append(this->userPresetPath).append(ruleName);
    return this->SaveRule(tmp, rule);
}

/**
 * @brief RulesManager::SaveStashPreset
 * @param rule
 * @return
 */
int RulesManager::SaveStashPreset(QString ruleName, QString rule) {
    QString tmp;
    tmp.append(this->stashesPresetPath).append(ruleName);
    return this->SaveRule(tmp, rule);
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
void RulesManager::checkDirs() {
    QStringList paths;
    paths << this->fullRulePath << this->userPresetPath << this->stashesPresetPath;
    for(int i = 0; i < paths.size(); ++i) {
        QFileInfo tmp(paths.at(i));
        if(!tmp.exists() || !tmp.isDir()) {
            QProcess tmpProcess;
            tmpProcess.start("mkdir -p " + paths.at(i));
            tmpProcess.waitForFinished(10);
        }
    }
}
