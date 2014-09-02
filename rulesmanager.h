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
 * File: rulesmanager.h                                                   *
 **************************************************************************/

#ifndef RULESMANAGER_H
#define RULESMANAGER_H

#include <QObject>
#include <QProcess>
#include <QDir>
#include <QFileInfo>
#include <QFile>
#include <QUuid>
#include <QMessageBox>

#include "defines.h"
#include "settingsmanager.h"

/**
 * @brief The RulesManager class
 */
class RulesManager : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief RulesManager
     * @param parent
     */
    explicit RulesManager(QObject *parent = 0);
    /**
     * @brief getSharedInstance
     * @return
     */
    static RulesManager* getSharedInstance();
    /**
     * @brief SaveRulesFromStash
     * @return
     */
    int SaveRulesFromStash(QString);
    /**
     * @brief SavePresetsFromStash
     * @return
     */
    int SavePresetsFromStash(QString);
    /**
     * @brief LoadStashRules
     * @return
     */
    Q_INVOKABLE QString LoadStashRules();
    /**
     * @brief LoadStashPresets
     * @return
     */
    Q_INVOKABLE QString LoadStashPresets();
    /**
     * @brief LoadUserRules
     * @return
     */
    Q_INVOKABLE QString LoadUserRules();
    /**
     * @brief GenerateUUID
     * @return
     */
    QString GenerateUUID();
    /**
     * @brief GetCurrentRulesetName
     * @return
     */
    Q_INVOKABLE QString GetCurrentRulesetName();
    /**
     * @brief SetCurrentRulesetname
     */
    Q_INVOKABLE void SetCurrentRulesetname(QString);
    /**
     * @brief DeleteUserRule
     * @return
     */
    Q_INVOKABLE bool DeleteUserRule(QString);
    /**
     * @brief DeleteUserRuleResponsive
     * @return
     */
    Q_INVOKABLE bool DeleteUserRuleResponsive(QString);
    /**
     * @brief ClearStashPresets
     * @return
     */
    int ClearStashPresets();
    /**
     * @brief SaveRule
     * @return
     */
    int SaveRule(QString, QString, bool);
    /**
     * @brief LoadRule
     * @return
     */
    QString LoadRule(QString);
    /**
     * @brief GetFullRulePath
     * @return
     */
    QString GetFullRulePath();

signals:

public slots:

private:
    /**
     * @brief CheckDirs
     */
    void CheckDirs();
    /**
     * @brief configBasePath
     */
    QString configBasePath;
    /**
     * @brief fullRulePath
     */
    QString fullRulePath;
    /**
     * @brief userPresetPath
     */
    QString userPresetPath;
    /**
     * @brief stashesPresetPath
     */
    QString stashesPresetPath;
    /**
     * @brief currentRulesetName
     */
    QString currentRulesetName;
};

#endif // RULESMANAGER_H
