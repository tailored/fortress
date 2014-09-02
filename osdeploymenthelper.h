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
 * File: osdeploymenthelper.h                                             *
 **************************************************************************/


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
