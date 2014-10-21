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
 * File: osdeploymenthelper.cpp                                           *
 **************************************************************************/

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
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QString rcLocalContents = file.readAll();
    qDebug() << rcLocalContents;
    file.close();
    if(rcLocalContents.contains("exit 0") && !rcLocalContents.contains(QString("").append(FORTRESS_RULES_BOOT_DEPLOYMENT_PATH).append("firewall.sh").append(""))) {
        qDebug() << "inside!";
        rcLocalContents.replace("exit 0",QString(FORTRESS_RULES_BOOT_DEPLOYMENT_PATH).append("firewall.sh\nexit 0"));
        process.execute(SettingsManager::getSharedInstance()->getValue("settings/sudoprovider"),
                        QStringList() << QString("echo \"").append(rcLocalContents).append("\" > /etc/rc.local"));
    }

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
    QFile file("/etc/rc.local");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QString rcLocalContents = file.readAll();
    if(rcLocalContents.contains(QString("").append(FORTRESS_RULES_BOOT_DEPLOYMENT_PATH).append("firewall.sh").append(""))) {
        rcLocalContents.replace(QString("").append(FORTRESS_RULES_BOOT_DEPLOYMENT_PATH).append("firewall.sh").append(""),"");
        process.execute(SettingsManager::getSharedInstance()->getValue("settings/sudoprovider"),
                        QStringList() << QString("echo `").append(rcLocalContents).append("` > /etc/rc.local"));
    }
}
