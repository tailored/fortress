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
 * File: fortressgenerator.h                                              *
 **************************************************************************/

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
#include <QStringList>

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
