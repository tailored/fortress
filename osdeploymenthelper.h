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

    static void gentooRemove();
    static void ubuntuRemove();
    static void fedoraRemove();

signals:

public slots:

};

#endif // OSDEPLOYMENTHELPER_H
