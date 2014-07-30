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
        QTextStream out(&fp);
        out << this->injectCode(retVal);
        fp.close();
        return true;
    } else return false;
}
