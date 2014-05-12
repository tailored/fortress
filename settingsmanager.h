#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QObject>
#include <QSettings>
#include <QDebug>
#include <QCoreApplication>
#include <QProcess>
#include <QStringList>
#include <QFileInfo>

#include "defines.h"

class SettingsManager : public QObject
{
    Q_OBJECT
public:
    explicit SettingsManager(QObject *parent = 0);
    static SettingsManager* getSharedInstance();
    Q_INVOKABLE QString getValue(QString key);
    Q_INVOKABLE bool setValue(QString key, QString val);
    Q_INVOKABLE void initConfig();
    Q_INVOKABLE QString validateSettings();

private:
    bool detectSudoProvider();
    bool detectIptables();
    bool checkFileExists(QString file);
    bool checkFileExecutable(QString file);

signals:

public slots:

// Variables
private:
    QSettings *settings;

};

#endif // SETTINGSMANAGER_H
