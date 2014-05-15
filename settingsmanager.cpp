#include "settingsmanager.h"

static SettingsManager* settingsMangerInstance = NULL;

/**
 * @brief SettingsManager::SettingsManager
 * @param parent
 */
SettingsManager::SettingsManager(QObject *parent) :
    QObject(parent)
{
    this->settings = new QSettings(FORTRESS_ORGANISATION, FORTRESS_APPLICATION);
    //if(this->getValue("settings/firstrun").compare("false") != 0) this->initConfig();
    this->getStashesList();
}

/**
 * @brief SettingsManager::getSharedInstance
 * @return
 */
SettingsManager* SettingsManager::getSharedInstance() {
    if(settingsMangerInstance == NULL) settingsMangerInstance = new SettingsManager;
    return settingsMangerInstance;
}

/**
 * @brief SettingsManager::getValue
 * @param key
 * @return
 */
QString SettingsManager::getValue(QString key) {
    return this->settings->value(key).toString();
}

/**
 * @brief SettingsManager::setValue
 * @param key
 * @param val
 * @return
 */
bool SettingsManager::setValue(QString key, QString val) {
    this->settings->setValue(key,val);
    return false;
}

/**
 * @brief SettingsManager::initConfig
 */
void SettingsManager::initConfig() {
    this->detectSudoProvider();
    this->detectIptables();
    this->setValue("settings/firstrun", "false");
}

/**
 * @brief SettingsManager::detectSudoProvider
 * @return
 */
bool SettingsManager::detectSudoProvider(bool writeConfig) {
    bool detected = false;
    QProcess process;
    QString output;
    QStringList sudoProviders;
    sudoProviders << "gksu" << "pkexec" << "kdesu";
    for(int i = 0; i < sudoProviders.size(); ++i) {
        if(!detected) {
            QString tmpString = "which ";
            tmpString.append(sudoProviders.at(i));
            process.start(tmpString);
            process.waitForFinished(20);
            output = process.readAllStandardOutput();
            output.remove(QRegExp("[\\n\\t\\r]"));
            if(writeConfig) this->setValue("settings/sudoprovider", output);
            detected = true;
        } else {
            break;
        }
    }
    return detected;
}

/**
 * @brief SettingsManager::detectIptables
 * @return
 */
bool SettingsManager::detectIptables(bool writeConfig) {
    bool detected = false;
    QStringList tmpList;
    tmpList << "/sbin/iptables" << "/usr/sbin/iptables" << "/usr/bin/iptables" << "/usr/local/sbin/iptables" << "/usr/local/bin/iptables";
    for(int i = 0; i < tmpList.size(); ++i) {
        if(!detected) {
            QFileInfo tmpInfo(tmpList.at(i));
            if(tmpInfo.isExecutable()) {
                detected = true;
                if(writeConfig) this->setValue("settings/iptables", tmpList.at(i));
            }
        } else {
            break;
        }
    }
    return detected;
}

/**
 * @brief SettingsManager::checkExecutable
 * @param file
 * @return
 */
bool SettingsManager::checkFileExecutable(QString file) {
    QFileInfo tmpFile(file);
    return tmpFile.isExecutable();
}

/**
 * @brief SettingsManager::checkFileExists
 * @param file
 * @return
 */
bool SettingsManager::checkFileExists(QString file) {
    QFileInfo tmpFile(file);
    return tmpFile.exists();
}

/**
 * @brief SettingsManager::validateSettings
 * @return
 */
QString SettingsManager::validateSettings() {
    bool errorFound = false, serializerSuccess;
    QVariantMap errors;
    QJson::Serializer serializer;
    QByteArray json;
    QVariantList tmpJsonList;
    // errors for graphical sudoprovider installation
    if(this->getValue("settings/sudoprovider").compare("") == 0 || !this->detectSudoProvider(false)) {
        QVariantMap tmpMap; tmpMap.insert(FORTRESS_KEYWORD_ERROR, FORTRESS_ERROR_SUDOPROVIDER_NOT_INSTALLED);
        tmpJsonList.append(tmpMap);
        errorFound = true;
    }
    if((this->getValue("settings/sudoprovider").compare("") != 0 || this->detectSudoProvider(false))) {
        if(!this->checkFileExists(this->getValue("settings/sudoprovider"))) {
            QVariantMap tmpMap; tmpMap.insert(FORTRESS_KEYWORD_ERROR, FORTRESS_ERROR_SUDOPROVIDER_NOT_FOUND);
            tmpJsonList.append(tmpMap);
            errorFound = true;
        }
        if(!this->checkFileExecutable(this->getValue("settings/sudoprovider"))) {
            QVariantMap tmpMap; tmpMap.insert(FORTRESS_KEYWORD_ERROR, FORTRESS_ERROR_SUDOPROVIDER_NOT_EXECUTABLE);
            tmpJsonList.append(tmpMap);
            errorFound = true;
        }
    }

    // errors for iptables installation
    if(this->getValue("settings/iptables").compare("") == 0 || !this->detectIptables(false)) {
        QVariantMap tmpMap; tmpMap.insert(FORTRESS_KEYWORD_ERROR, FORTRESS_ERROR_IPTABLES_NOT_INSTALLED);
        tmpJsonList.append(tmpMap);
        errorFound = true;
    }
    if(this->getValue("settings/iptables").compare("") != 0 || this->detectIptables(false)) {
        if(!this->checkFileExists(this->getValue("settings/iptables"))) {
            QVariantMap tmpMap; tmpMap.insert(FORTRESS_KEYWORD_ERROR, FORTRESS_ERROR_IPTABLES_NOT_FOUND);
            tmpJsonList.append(tmpMap);
            errorFound = true;
        }
        if(!this->checkFileExecutable(this->getValue("settings/iptables"))) {
            QVariantMap tmpMap; tmpMap.insert(FORTRESS_KEYWORD_ERROR, FORTRESS_ERROR_IPTABLES_NOT_EXECUTABLE);
            tmpJsonList.append(tmpMap);
            errorFound = true;
        }
    }
    // append generic error message
    if(errorFound)  {
        QVariantMap tmpMap; tmpMap.insert(FORTRESS_KEYWORD_WARNING, FORTRESS_ERROR_CHECK_ENTRIES);
        tmpJsonList.insert(tmpJsonList.begin(), tmpMap);

        errors.insert(FORTRESS_KEYWORD_USERFEEDBACK, tmpJsonList);
        //json = serializer.serialize(errors, &serializerSuccess);
    }
    return json;
}

/**
 * @brief SettingsManager::getStashesList
 * @return
 */
QString SettingsManager::getStashesList() {
    return this->stashesList;
}

/**
 * @brief SettingsManager::setStashesList
 * @param slist
 */
void SettingsManager::setStashesList(QByteArray slist) {
    this->stashesList = slist;
}
