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
    sudoProviders << "gksu" << "kdesu";
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
    bool errorFound = false;
    QString retVal;
    // errors for graphical sudoprovider installation
    if(this->getValue("settings/sudoprovider").compare("") == 0 || !this->detectSudoProvider(FALSE)) {
        retVal.append("<li>").append(ERROR_SUDOPROVIDER_NOT_INSTALLED).append("</li>");
        errorFound = true;
    }
    if((this->getValue("settings/sudoprovider").compare("") != 0 || this->detectSudoProvider(FALSE))) {
        if(!this->checkFileExists(this->getValue("settings/sudoprovider"))) {
            retVal.append("<li>").append(ERROR_SUDOPROVIDER_NOT_FOUND).append("</li>");
            errorFound = true;
        }
        if(!this->checkFileExecutable(this->getValue("settings/sudoprovider"))) {
            retVal.append("<li>").append(ERROR_SUDOPROVIDER_NOT_EXECUTABLE).append("</li>");
            errorFound = true;
        }
    }

    // errors for iptables installation
    if(this->getValue("settings/iptables").compare("") == 0 || !this->detectIptables(FALSE)) {
        retVal.append("<li>").append(ERROR_IPTABLES_NOT_INSTALLED).append("</li>");
        errorFound = true;
    }
    if(this->getValue("settings/iptables").compare("") != 0 || this->detectIptables(FALSE)) {
        if(!this->checkFileExists(this->getValue("settings/iptables"))) {
            retVal.append("<li>").append(ERROR_IPTABLES_NOT_FOUND).append("</li>");
            errorFound = true;
        }
        if(!this->checkFileExecutable(this->getValue("settings/iptables"))) {
            retVal.append("<li>").append(ERROR_IPTABLES_NOT_EXECUTABLE).append("</li>");
        }
    }
    // append generic error message
    if(errorFound)  {
        QString tmp = "<b>ERROR:</b><ul>";
        retVal.append("<li>").append(ERROR_CHECK_ENTRIES).append("</li>");
        tmp.append(retVal);
        tmp.append("</ul>");
        retVal = tmp;
    }
    // return error(s))
    return retVal;
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
