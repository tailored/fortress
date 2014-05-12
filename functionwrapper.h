#ifndef FUNCTIONWRAPPER_H
#define FUNCTIONWRAPPER_H

#include <QObject>
#include <QApplication>
#include <QString>

#include "defines.h"

class functionWrapper : public QObject
{
    Q_OBJECT
public:
    explicit functionWrapper(QObject *parent = 0);

signals:

public:
    Q_INVOKABLE QString getDebugOutput();
};

#endif // FUNCTIONWRAPPER_H
