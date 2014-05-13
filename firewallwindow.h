#ifndef FIREWALLWINDOW_H
#define FIREWALLWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
#include <QWebView>
#include <QWebFrame>
#include <QDebug>

#include "functionwrapper.h"
#include "settingsmanager.h"
#include "defines.h"
#include "filedownloader.h"
#include "settingsmanager.h"

namespace Ui {
class fireWallWindow;
}

class fireWallWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit fireWallWindow(QWidget *parent = 0);
    ~fireWallWindow();
    void updateWebView();

private slots:
    void on_fireWallWebView_loadFinished(bool arg1);
    void setStashesList();
private:
    Ui::fireWallWindow *ui;
    functionWrapper *fwrapper;
    QWebView *firewallWebView;
    FileDownloader *fdl;
};

#endif // FIREWALLWINDOW_H
