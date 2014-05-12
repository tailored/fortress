#include "settingsmanager.h"

static SettingsManager* instance = NULL;

/**
 * @brief SettingsManager::SettingsManager
 * @param parent
 */
SettingsManager::SettingsManager(QObject *parent) :
    QObject(parent)
{
    this->settings = new QSettings(FORTRESS_ORGANISATION, FORTRESS_APPLICATION);
    if(this->getValue("settings/sudoprovider").compare("") == 0) this->initConfig();
}

/**
 * @brief SettingsManager::getSharedInstance
 * @return
 */
SettingsManager* SettingsManager::getSharedInstance() {
    if(instance == NULL) instance = new SettingsManager;
    return instance;
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
}

/**
 * @brief SettingsManager::detectSudoProvider
 * @return
 */
bool SettingsManager::detectSudoProvider() {
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
            this->setValue("settings/sudoprovider", output);
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
bool SettingsManager::detectIptables() {
    bool detected = false;
    QStringList tmpList;
    tmpList << "/sbin/iptables" << "/usr/sbin/iptables" << "/usr/bin/iptables" << "/usr/local/sbin/iptables" << "/usr/local/bin/iptables";
    for(int i = 0; i < tmpList.size(); ++i) {
        if(!detected) {
            QFileInfo tmpInfo(tmpList.at(i));
            if(tmpInfo.isExecutable()) {
                detected = true;
                this->setValue("settings/iptables", tmpList.at(i));
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
    if(!this->checkFileExists(this->getValue("settings/sudoprovider"))) {
        retVal.append(ERROR_SUDOPROVIDER_NOT_FOUND).append(GENERIC_HTML_LINEBREAK);
        errorFound = true;
    }
    if(!this->checkFileExecutable(this->getValue("settings/sudoprovider"))) {
        retVal.append(ERROR_SUDOPROVIDER_NOT_EXECUTABLE).append(GENERIC_HTML_LINEBREAK);
        errorFound = true;
    }
    if(!this->checkFileExists(this->getValue("settings/iptables"))) {
        retVal.append(ERROR_IPTABLES_NOT_FOUND).append(GENERIC_HTML_LINEBREAK);
        errorFound = true;
    }
    if(!this->checkFileExecutable(this->getValue("settings/iptables"))) {
        retVal.append(ERROR_IPTABLES_NOT_EXECUTABLE).append(GENERIC_HTML_LINEBREAK);
    }
    if(errorFound) retVal.append(ERROR_CHECK_ENTRIES).append(GENERIC_HTML_LINEBREAK);
    return retVal;
}
