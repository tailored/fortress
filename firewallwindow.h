#ifndef FIREWALLWINDOW_H
#define FIREWALLWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
#include <QWebView>
#include <QWebFrame>
#include <QDebug>
#include <QStyle>
#include <QFileDialog>
#include <QMessageBox>

#include "settingsmanager.h"
#include "defines.h"
#include "filedownloader.h"
#include "settingsmanager.h"
#include "fortressgenerator.h"
#include "rulesmanager.h"

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
    Q_INVOKABLE void updateStashesContent();
private slots:
    void on_fireWallWebView_loadFinished(bool arg1);
    void setStashesList();
    void setRulesList();
    void setPresetsList();
    void on_actionExport_triggered();
    void exportFileChoosen(QString);

private:
    Ui::fireWallWindow *ui;
    FileDownloader *fdl, *rDl, *pDl;

protected:
    void resizeEvent(QResizeEvent *);
};

#endif // FIREWALLWINDOW_H
