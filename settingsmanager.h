#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QObject>
#include <QSettings>
#include <QDebug>
#include <QCoreApplication>
#include "defines.h"

class SettingsManager : public QObject
{
    Q_OBJECT
public:
    explicit SettingsManager(QObject *parent = 0);
    static SettingsManager* getSharedInstance();
    Q_INVOKABLE QString getValue(QString key);
    Q_INVOKABLE bool setValue(QString key, QString val);
signals:

public slots:

private:
    QSettings *settings;

};

#endif // SETTINGSMANAGER_H
