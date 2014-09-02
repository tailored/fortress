#ifndef OSDEPLOYMENTHELPER_H
#define OSDEPLOYMENTHELPER_H

#include <QObject>
#include <QProcess>
#include <QDebug>

#include "settingsmanager.h"


class OsDeploymentHelper : public QObject
{
    Q_OBJECT
public:
    static void gentooDeploy();
    static void ubuntuDeploy();
    static void fedoraDeploy();
    static void redhatDeploy();
    static void suseDeploy();
    static void archDeploy();

    static void gentooRemove();
    static void ubuntuRemove();
    static void fedoraRemove();
    static void redhatRemove();
    static void suseRemove();
    static void archRemove();

signals:

public slots:

};

#endif // OSDEPLOYMENTHELPER_H
