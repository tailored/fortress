/**************************************************************************
 * Copyright (C) 2014  - Christian Richter                                *
 *                     - Daniel Niedermeyer                               *
 *                     - Benjamin Hiefner                                 *
 *                                                                        *
 * This program is free software: you can redistribute it and/or modify   *
 * it under the terms of the GNU General Public License as published by   *
 * the Free Software Foundation, either version 3 of the License, or      *
 * (at your option) any later version.                                    *
 *                                                                        *
 * This program is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 * GNU General Public License for more details.                           *
 *                                                                        *
 * You should have received a copy of the GNU General Public License      *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>   *
 **************************************************************************
 * File: firewallwindow.h                                                 *
 **************************************************************************/

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
#include <QProcess>
#include <QStringList>
#include <QMessageBox>
#include <QWebInspector>

#include "settingsmanager.h"
#include "defines.h"
#include "filedownloader.h"
#include "settingsmanager.h"
#include "fortressgenerator.h"
#include "rulesmanager.h"
#include "osdeploymenthelper.h"

namespace Ui {
class fireWallWindow;
}

/**
 * @brief The fireWallWindow class
 */
class fireWallWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief fireWallWindow
     * @param parent
     */
    explicit fireWallWindow(QWidget *parent = 0);
    /**
      * @brief ~fireWallWindow
      */
    ~fireWallWindow();
    /**
     * @brief updateWebView
     */
    void updateWebView();

public slots:
    /**
     * @brief updateStashesContent
     */
    Q_INVOKABLE void updateStashesContent();
    /**
     * @brief on_actionUpdateRemote_triggered
     */
    Q_INVOKABLE void on_actionUpdateRemote_triggered();
    /**
     * @brief on_actionSave_triggered
     */
    Q_INVOKABLE void on_actionSave_triggered();
    /**
     * @brief getCurrentConfig
     * @return
     */
    Q_INVOKABLE QString getCurrentConfig();
    /**
     * @brief saveAs
     * @param proposedName
     */
    Q_INVOKABLE void saveAs(QString proposedName);

private slots:
    /**
     * @brief on_fireWallWebView_loadFinished
     * @param arg1
     */
    void on_fireWallWebView_loadFinished(bool arg1);
    /**
     * @brief setStashesList
     */
    void setStashesList();
    /**
     * @brief setRulesList
     */
    void setRulesList();
    /**
     * @brief setPresetsList
     */
    void setPresetsList();
    /**
     * @brief on_actionExport_triggered
     */
    void on_actionExport_triggered();
    /**
     * @brief exportFileChoosen
     */
    void exportFileChoosen(QString);
    /**
     * @brief updateFinished
     */
    void updateFinished();
    /**
     * @brief osIsSupported
     * @return
     */
    bool osIsSupported();
    /**
     * @brief on_actionDeploy_triggered
     */
    void on_actionDeploy_triggered();
    /**
     * @brief on_actionClear_triggered
     */
    void on_actionClear_triggered();
    /**
     * @brief on_actionQuit_triggered
     */
    void on_actionQuit_triggered();
    /**
     * @brief on_actionSaveAs_triggered
     */
    void on_actionSaveAs_triggered();
    /**
     * @brief on_actionDebploy_on_Boot_triggered
     */
    void on_actionDebploy_on_Boot_triggered();
    /**
     * @brief on_actionRemove_from_Boot_triggered
     */
    void on_actionRemove_from_Boot_triggered();

private:
    /**
     * @brief ui
     */
    Ui::fireWallWindow *ui;
    /**
     * @brief fdl
     */
    FileDownloader *fdl, *rDl, *pDl;
    /**
     * @brief rulesDone
     */
    bool rulesDone;
    /**
     * @brief presetsDone
     */
    bool presetsDone;

protected:
    /**
     * @brief resizeEvent
     */
    void resizeEvent(QResizeEvent *);
};

#endif // FIREWALLWINDOW_H
