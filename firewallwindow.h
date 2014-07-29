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
#include <QInputDialog>

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
private slots:
    void on_fireWallWebView_loadFinished(bool arg1);
    void setStashesList();
    void setRulesList();
    void setPresetsList();
    void on_actionExport_triggered();
    void exportFileChoosen(QString);
    void updateFinished();
    Q_INVOKABLE void updateStashesContent();
    Q_INVOKABLE void on_actionUpdateRemote_triggered();
    Q_INVOKABLE void on_actionSave_triggered();
    Q_INVOKABLE QString getCurrentConfig();

    void on_actionDeploy_triggered();

    void on_actionClear_triggered();

    void on_actionQuit_triggered();

private:
    Ui::fireWallWindow *ui;
    FileDownloader *fdl, *rDl, *pDl;
    bool rulesDone;
    bool presetsDone;

protected:
    void resizeEvent(QResizeEvent *);
};

#endif // FIREWALLWINDOW_H
