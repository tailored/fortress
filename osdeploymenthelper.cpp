#include "osdeploymenthelper.h"

/**
 * @brief OsDeploymentHelper::gentooDeploy
 */
void OsDeploymentHelper::gentooDeploy() {
    QProcess process;
    process.execute(SettingsManager::getSharedInstance()->getValue("settings/sudoprovider"),
                    QStringList() << QString("ln -s ").append(FORTRESS_RULES_BOOT_DEPLOYMENT_PATH).append("firewall.sh").append(" /etc/local.d/firewall.start"));
}

/**
 * @brief OsDeploymentHelper::ubuntuDeploy
 */
void OsDeploymentHelper::ubuntuDeploy() {
    QProcess process;
    process.execute(SettingsManager::getSharedInstance()->getValue("settings/sudoprovider"),
                    QStringList() << QString("cp /etc/rc.local /etc/rc.local.fortressbackup"));
    QFile file("/etc/rc.local");
    QString rcLocalContents = file.readAll();
    if(rcLocalContents.contains("/exit 0/") && rcLocalContents.contains(QString("/").append(FORTRESS_RULES_BOOT_DEPLOYMENT_PATH).append("firewall.sh").append("/"))) {
        rcLocalContents.replace("/exit 0/",QString(FORTRESS_RULES_BOOT_DEPLOYMENT_PATH).append("firewall.sh\nexit 0"));
        process.execute(SettingsManager::getSharedInstance()->getValue("settings/sudoprovider"),
                        QStringList() << QString("echo `").append(rcLocalContents).append("`"));
    }

}

/**
 * @brief OsDeploymentHelper::fedoraDeploy
 */
void OsDeploymentHelper::fedoraDeploy() {

}

/**
 * @brief OsDeploymentHelper::gentooRemove
 */
void OsDeploymentHelper::gentooRemove() {
    QProcess process;
    process.execute(SettingsManager::getSharedInstance()->getValue("settings/sudoprovider"),
                    QStringList() << QString("rm /etc/local.d/firewall.start"));
}

/**
 * @brief OsDeploymentHelper::ubuntuRemove
 */
void OsDeploymentHelper::ubuntuRemove() {
    QProcess process;
    QFIle("/etc/rc.local");
    QString rcLocalContents = file.readAll();
    if(rcLocalContents.contains(QString("/").append(FORTRESS_RULES_BOOT_DEPLOYMENT_PATH).append("firewall.sh").append("/"))) {
        rcLocalContents.replace(QString("/").append(FORTRESS_RULES_BOOT_DEPLOYMENT_PATH).append("firewall.sh").append("/"),"");
        process.execute(SettingsManager::getSharedInstance()->getValue("settings/sudoprovider"),
                        QStringList() << QString("echo `").append(rcLocalContents).append("`"));
    }
}

/**
 * @brief OsDeploymentHelper::fedoraRemove
 */
void OsDeploymentHelper::fedoraRemove() {

}
