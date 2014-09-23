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
 * File: fortressgenerator.cpp                                            *
 **************************************************************************/

#include "fortressgenerator.h"

/**
 * @brief fortressGeneratorInstance
 */
static FortressGenerator* fortressGeneratorInstance = NULL;

/**
 * @brief FortressGenerator::getSharedInstance
 * @return
 */
FortressGenerator* FortressGenerator::getSharedInstance() {
    if(fortressGeneratorInstance == NULL) fortressGeneratorInstance = new FortressGenerator;
    return fortressGeneratorInstance;
}

/**
 * @brief FortressGenerator::FortressGenerator
 * @param parent
 */
FortressGenerator::FortressGenerator(QObject *parent) :
    QObject(parent)
{
    QFile file(":/templates/templates/firewall.sh.template");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QByteArray dump = file.readAll();
    this->setFortressTemplateString(dump);
}


/**
 * @brief FortressGenerator::getFortressTemplateString
 * @return
 */
QString FortressGenerator::getFortressTemplateString() {
    return this->fortressTemplateString;
}
/**
 * @brief FortressGenerator::setFortressTemplateString
 * @param tplString
 */
void FortressGenerator::setFortressTemplateString(QString tplString) {
    this->fortressTemplateString = tplString;
}

/**
 * @brief FortressGenerator::injectCode
 * @param code
 * @return
 */
QString FortressGenerator::injectCode(QString code) {
    QString retVal = this->getFortressTemplateString();
    retVal.replace("iptables",SettingsManager::getSharedInstance()->getValue("settings/iptables"));
    retVal.replace(FORTRESS_GENERATOR_REPLACE_TOKEN, code);
    return retVal;
}

/**
 * @brief FortressGenerator::exportFirewallScript
 * @param fn
 * @return
 */
bool FortressGenerator::exportFirewallScript(QString fn, QString rs) {
    QFile fp(fn);
    bool ok;
    QJson::Parser *parser = new QJson::Parser;
    QByteArray rules(rs.toLatin1(),rs.length());
    QVariantList jsonObject = parser->parse(rules,&ok).toList();
    QString retVal = "";
    for(QVariantList::Iterator it = jsonObject.begin(); it!=jsonObject.end();++it) {
        QVariantMap mp = it->toMap();
        if(mp.value("protocol").toMap().value("udp").toBool() == true) {
            // create udp rule
            retVal.append("# ").append(mp.value("name").toString()).append(" (udp)\n");
            retVal.append("# --------------------------------------------------------------\n");
            retVal.append(SettingsManager::getSharedInstance()->getValue("settings/iptables"));
            retVal.append(" -A INPUT -p tcp");
            if(mp.value("port").toString().compare("0") != 0 && !mp.value("port").toString().isEmpty())
                retVal.append(" --dport ").append(mp.value("port").toString());
            if(mp.value("addr").toString().compare("") != 0 && !mp.value("addr").toString().isEmpty())
                retVal.append(" -s ").append(mp.value("addr").toString());
            retVal.append(" -j ACCEPT\n\n");
        }
        if(mp.value("protocol").toMap().value("tcp").toBool() == true) {
            // create tcp rule
            retVal.append("# ").append(mp.value("name").toString()).append(" (tcp)\n");
            retVal.append("# --------------------------------------------------------------\n");
            retVal.append(SettingsManager::getSharedInstance()->getValue("settings/iptables"));
            retVal.append(" -A INPUT -p tcp");
            if(mp.value("port").toString().compare("0") != 0 && !mp.value("port").toString().isEmpty())
                retVal.append(" --dport ").append(mp.value("port").toString());
            if(!mp.value("addr").toString().isEmpty())
                retVal.append(" -s ").append(mp.value("addr").toString());
            retVal.append(" -j ACCEPT\n\n");        }
        }
    if(fp.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        fp.setPermissions(QFile::ExeGroup  | QFile::ExeOther   | QFile::ExeOwner  | QFile::ExeUser|
                          QFile::ReadGroup | QFile::ReadOther  | QFile::ReadOwner | QFile::ReadUser|
                          QFile::WriteUser | QFile::WriteOwner);
        QTextStream out(&fp);
        out << this->injectCode(retVal);
        fp.close();
        return true;
    } else return false;
}
