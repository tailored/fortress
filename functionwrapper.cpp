#include "functionwrapper.h"

functionWrapper::functionWrapper(QObject *parent) :
    QObject(parent)
{
}

QString functionWrapper::getDebugOutput() {
    qDebug("functionwrapper: debugoutput triggered!");
    QString tmp;
    tmp.append("this is a debug output from qt c++ code");
    return tmp;
}
