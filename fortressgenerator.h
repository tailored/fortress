#ifndef FORTRESSGENERATOR_H
#define FORTRESSGENERATOR_H

#include <QObject>
#include <QFile>
#include <QDebug>
#include <QUrl>
#include <qjson/parser.h>
#include <QVariant>
#include <QVariantMap>
#include <QMap>

#include "defines.h"
#include "rulesmanager.h"

/**
 * @brief The FortressGenerator class
 */
class FortressGenerator : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief FortressGenerator
     * @param parent
     */
    explicit FortressGenerator(QObject *parent = 0);
    /**
     * @brief getSharedInstance
     * @return
     */
    static FortressGenerator* getSharedInstance();
    /**
     * @brief getFortressTemplateString
     * @return
     */
    QString getFortressTemplateString();
    /**
     * @brief injectCode
     * @return
     */
    QString injectCode(QString);
    /**
     * @brief exportFirewallScript
     * @return
     */
    bool exportFirewallScript(QString, QString);

private:
    /**
     * @brief fortressTemplateString
     */
    QString fortressTemplateString;
    /**
     * @brief setFortressTemplateString
     */
    void setFortressTemplateString(QString);

signals:

public slots:
};

#endif // FORTRESSGENERATOR_H
