#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QObject>
#include <QSettings>
#include <QDebug>
#include <QCoreApplication>
#include <QProcess>
#include <QStringList>
#include <QFileInfo>
#include <QThread>
#include <qjson/serializer.h>
#include <QNetworkInterface>
#include <QDir>
#include <QStringList>
#include <QRegExp>

#include "defines.h"
#include "filedownloader.h"

/**
 * @brief The SettingsManager class
 */
class SettingsManager : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief SettingsManager
     * @param parent
     */
    explicit SettingsManager(QObject *parent = 0);
    /**
     * @brief getSharedInstance
     * @return
     */
    static SettingsManager* getSharedInstance();
    /**
     * @brief setStashesList
     * @param slist
     */
    void setStashesList(QByteArray slist);
    /**
     * @brief getValue
     * @param key
     * @return
     */
    Q_INVOKABLE QString getValue(QString key);
    /**
     * @brief setValue
     * @param key
     * @param val
     * @return
     */
    Q_INVOKABLE bool setValue(QString key, QString val);
    /**
     * @brief initConfig
     */
    Q_INVOKABLE void initConfig();
    /**
     * @brief validateSettings
     * @return
     */
    Q_INVOKABLE QString validateSettings();
    /**
     * @brief getStashesList
     * @return
     */
    Q_INVOKABLE QString getStashesList();
    /**
     * @brief getNetWorkInterfaces
     * @return
     */
    Q_INVOKABLE QString getNetWorkInterfaces();
    /**
     * @brief detectSudoProvider
     * @param writeConfig
     * @return
     */
    Q_INVOKABLE bool detectSudoProvider(bool writeConfig = true);
    /**
     * @brief detectIptables
     * @param writeConfig
     * @return
     */
    Q_INVOKABLE bool detectIptables(bool writeConfig = true);
    /**
     * @brief detectOS
     * @return
     */
    Q_INVOKABLE bool detectOS();
    /**
     * @brief getFullSettingsPath
     * @return
     */
    QString getFullSettingsPath();

private:
    /**
     * @brief checkFileExists
     * @param file
     * @return
     */
    bool checkFileExists(QString file);
    /**
     * @brief checkFileExecutable
     * @param file
     * @return
     */
    bool checkFileExecutable(QString file);
    /**
     * @brief stashesList
     */
    QString stashesList;
signals:

public slots:

// Variables
private:
    /**
     * @brief settings
     */
    QSettings *settings;

};

#endif // SETTINGSMANAGER_H
