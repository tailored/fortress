#ifndef RULESMANAGER_H
#define RULESMANAGER_H

#include <QObject>
#include <QProcess>
#include <QDir>
#include <QFileInfo>
#include <QFile>

#include "defines.h"
#include "settingsmanager.h"

class RulesManager : public QObject
{
    Q_OBJECT
public:
    explicit RulesManager(QObject *parent = 0);
    QString GenarateScriptFromRule(QString);
    static RulesManager* getSharedInstance();
    int SaveUserPreset(QString, QString);
    int SaveStashPreset(QString, QString);
    QString LoadUserPreset(QString);
    QString LoadStashPreset(QString);
    bool FetchRemoteStashes();
    int ClearStashPresets();

signals:

public slots:

private:
    void checkDirs();
    int SaveRule(QString, QString);
    QString LoadRule(QString);
    QString configBasePath;
    QString fullRulePath;
    QString userPresetPath;
    QString stashesPresetPath;
};

#endif // RULESMANAGER_H
