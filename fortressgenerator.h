#ifndef FORTRESSGENERATOR_H
#define FORTRESSGENERATOR_H

#include <QObject>
#include <QFile>
#include <QDebug>
#include <QUrl>
#include <qjson/parser.h>

#include "defines.h"
#include "rulesmanager.h"

class FortressGenerator : public QObject
{
    Q_OBJECT
public:
    explicit FortressGenerator(QObject *parent = 0);
    static FortressGenerator* getSharedInstance();
    QString getFortressTemplateString();
    QString injectCode(QString);
    bool exportFirewallScript(QString, QString);

private:
    QString fortressTemplateString;
    void setFortressTemplateString(QString);

signals:

public slots:
};

#endif // FORTRESSGENERATOR_H
