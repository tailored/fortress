#include "osdeploymenthelper.h"

void OsDeploymentHelper::gentooDeploy() {
    QProcess process;
    process.execute(SettingsManager::getSharedInstance()->getValue("settings/sudoprovider"),
                    QStringList() << QString("ln -s ").append(FORTRESS_RULES_BOOT_DEPLOYMENT_PATH).append("firewall.sh").append(" /etc/local.d/firewall.start"));
}

void OsDeploymentHelper::ubuntuDeploy() {

}

void OsDeploymentHelper::fedoraDeploy() {

}

void OsDeploymentHelper::suseDeploy() {

}

void OsDeploymentHelper::archDeploy() {

}

void OsDeploymentHelper::gentooRemove() {
    QProcess process;
    process.execute(SettingsManager::getSharedInstance()->getValue("settings/sudoprovider"),
                    QStringList() << QString("rm /etc/local.d/firewall.start"));
}

void OsDeploymentHelper::ubuntuRemove() {

}

void OsDeploymentHelper::fedoraRemove() {

}

void OsDeploymentHelper::redhatRemove() {

}

void OsDeploymentHelper::suseRemove() {

}

void OsDeploymentHelper::archRemove() {

}
