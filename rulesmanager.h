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
