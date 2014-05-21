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
    retVal.replace(FORTRESS_GENERATOR_REPLACE_TOKEN, code);
    return retVal;
}
