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
#include "filedownloader.h"

class SettingsManager : public QObject
{
    Q_OBJECT
public:
    explicit SettingsManager(QObject *parent = 0);
    static SettingsManager* getSharedInstance();
    void setStashesList(QByteArray slist);
    Q_INVOKABLE QString getValue(QString key);
    Q_INVOKABLE bool setValue(QString key, QString val);
    Q_INVOKABLE void initConfig();
    Q_INVOKABLE QString validateSettings();
    Q_INVOKABLE QString getStashesList();


private:
    bool detectSudoProvider(bool writeConfig = TRUE);
    bool detectIptables(bool writeConfig = TRUE);
    bool checkFileExists(QString file);
    bool checkFileExecutable(QString file);
    QString stashesList;
signals:

public slots:

// Variables
private:
    QSettings *settings;

};

#endif // SETTINGSMANAGER_H
