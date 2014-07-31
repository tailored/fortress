#ifndef RULESMANAGER_H
#define RULESMANAGER_H

#include <QObject>
#include <QProcess>
#include <QDir>
#include <QFileInfo>
#include <QFile>
#include <QUuid>

#include "defines.h"
#include "settingsmanager.h"

class RulesManager : public QObject
{
    Q_OBJECT
public:
    explicit RulesManager(QObject *parent = 0);
    QString GenarateScriptFromRule(QString);
    static RulesManager* getSharedInstance();
    int SaveRulesFromStash(QString);
    int SavePresetsFromStash(QString);
    Q_INVOKABLE QString LoadStashRules();
    Q_INVOKABLE QString LoadStashPresets();
    Q_INVOKABLE QString LoadUserRules();
    Q_INVOKABLE QString GenerateUUID();
    Q_INVOKABLE QString GetCurrentRulesetName();
    Q_INVOKABLE void SetCurrentRulesetname(QString);
    Q_INVOKABLE bool DeleteUserRule(QString);
    int ClearStashPresets();
    int SaveRule(QString, QString, bool);
    QString LoadRule(QString);
    QString GetFullRulePath();

signals:

public slots:

private:
    void CheckDirs();
    QString configBasePath;
    QString fullRulePath;
    QString userPresetPath;
    QString stashesPresetPath;
    QString currentRulesetName;
};

#endif // RULESMANAGER_H
