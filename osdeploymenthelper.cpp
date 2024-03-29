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
    file.close();
    if(rcLocalContents.contains("exit 0") && !rcLocalContents.contains(QString("").append(FORTRESS_RULES_BOOT_DEPLOYMENT_PATH).append("firewall.sh").append(""))) {
        rcLocalContents.replace(QRegExp("[^\"]exit 0[^\"]"),QString(FORTRESS_RULES_BOOT_DEPLOYMENT_PATH).append("firewall.sh\nexit 0\n"));
        QFile file("/tmp/rc.local");
        file.open(QIODevice::WriteOnly|QIODevice::Text);
        file.write(rcLocalContents.toLocal8Bit());
        file.close();
        /*process.execute(SettingsManager::getSharedInstance()->getValue("settings/sudoprovider"),
                        QStringList() << QString("mv /tmp/rc.local /etc/rc.local"));
        process.execute(SettingsManager::getSharedInstance()->getValue("settings/sudoprovider"),
                        QStringList() << QString("chmod 0755 /etc/rc.local"));
        process.execute(SettingsManager::getSharedInstance()->getValue("settings/sudoprovider"),
                        QStringList() << QString("chown root:root /etc/rc.local"));*/
        qDebug() << "deploy";
        process.execute(SettingsManager::getSharedInstance()->getValue("settings/sudoprovider"),
                        QStringList() << QString("bash -c 'mv /tmp/rc.local /etc/rc.local; chmod 0755 /etc/rc.local; chown root:root /etc/rc.local'"));


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
    file.close();
    if(rcLocalContents.contains(QString("").append(FORTRESS_RULES_BOOT_DEPLOYMENT_PATH).append("firewall.sh").append(""))) {
        rcLocalContents.replace(QString("").append(FORTRESS_RULES_BOOT_DEPLOYMENT_PATH).append("firewall.sh").append(""),"");
        QFile file("/tmp/rc.local");
        file.open(QIODevice::WriteOnly|QIODevice::Text);
        file.write(rcLocalContents.toLocal8Bit());
        file.close();
        /*process.execute(SettingsManager::getSharedInstance()->getValue("settings/sudoprovider"),
                        QStringList() << QString("mv /tmp/rc.local /etc/rc.local"));
        process.execute(SettingsManager::getSharedInstance()->getValue("settings/sudoprovider"),
                        QStringList() << QString("chmod 0755 /etc/rc.local"));
        process.execute(SettingsManager::getSharedInstance()->getValue("settings/sudoprovider"),
                        QStringList() << QString("chown root:root /etc/rc.local"));*/
        process.execute(SettingsManager::getSharedInstance()->getValue("settings/sudoprovider"),
                        QStringList() << QString("bash -c 'mv /tmp/rc.local /etc/rc.local; chmod 0755 /etc/rc.local; chown root:root /etc/rc.local'"));
    }
}
