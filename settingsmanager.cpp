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
