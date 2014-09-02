#ifndef OSDEPLOYMENTHELPER_H
#define OSDEPLOYMENTHELPER_H

#include <QObject>
#include <QProcess>
#include <QDebug>

#include "settingsmanager.h"

/**
 * @brief The OsDeploymentHelper class
 */
class OsDeploymentHelper : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief gentooDeploy
     */
    static void gentooDeploy();
    /**
     * @brief ubuntuDeploy
     */
    static void ubuntuDeploy();

    /**
     * @brief gentooRemove
     */
    static void gentooRemove();
    /**
     * @brief ubuntuRemove
     */
    static void ubuntuRemove();

signals:

public slots:

};

#endif // OSDEPLOYMENTHELPER_H
