/**************************************************************************
 * Copyright (C) 2014  - Daniel Niedermeyer                               *
 *                     - Christian Richter                                *
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
 * File: settings.js                                                        *
 **************************************************************************/

function getSettings() {
  $("#settings-sudoprovider").val(smanager.getValue("settings/sudoprovider"));
  $("#settings-iptables").val(smanager.getValue("settings/iptables"));
  var currentStashUrl = smanager.getValue("settings/stashurl");
  var currentStashName = smanager.getValue("settings/stashname");
  var stashesList = JSON.parse(smanager.getStashesList());
  if (stashesList.hasOwnProperty("stashes")) {
    retVal = "<select name=\"settings-stashurl\" id=\"settings-stashurl\" class=\"form-control\">";
    for (var i = 0; i < stashesList.stashes.length; i++) {
      retVal += "<option value=\"" + stashesList.stashes[i].url + "\"";
      if (currentStashUrl == stashesList.stashes[i].url && currentStashName == stashesList.stashes[i].name)
        retVal += " selected=\"selected\" ";
      retVal += ">" + stashesList.stashes[i].name + "</option>";
    }
    retVal += "</select>";
  }
  $("#settings-stashlist-wrapper").html(retVal);
  $("#settings-os").val(smanager.getValue("settings/os"));
}

function setSettings() {
  var selectedStashUrl = $("#settings-stashurl");
  smanager.setValue("settings/sudoprovider", $("#settings-sudoprovider").val());
  smanager.setValue("settings/iptables", $("#settings-iptables").val());
  smanager.setValue("settings/stashurl", selectedStashUrl.val());
  smanager.setValue("settings/stashname", selectedStashUrl.find("option:selected").text());
  validateSettings();
  getSettings();
}

function autoDetectSettings() {
  smanager.initConfig();
  var stashesListString = smanager.getStashesList();
  if (stashesListString.length > 0) {
    var stashesList = JSON.parse(stashesListString);
    if (stashesList.hasOwnProperty("stashes")) {
      smanager.setValue("settings/stashurl", stashesList.stashes[0].url);
      smanager.setValue("settings/stashname", stashesList.stashes[0].name);
    }
  }
  validateSettings();
  getSettings();
  mwindow.updateStashesContent();
}

function validateSettings() {
  var tmpData = smanager.validateSettings();
  var errorDiv = $("#settingsError");
  var errorDivWrapper = $("#settingsErrorWrapper");
  errorDiv.html("");
  if (tmpData.length > 0) {
    var parseData = JSON.parse(tmpData);
    if (parseData.hasOwnProperty("userfeedback")) {
      parseData = parseData.userfeedback;
      if (parseData.length > 0) {
        for (var i = 0; i < parseData.length; i++) {
          if (parseData[i].hasOwnProperty("error")) {
            errorDiv.append("<div class=\"alert alert-danger\">" + parseData[i].error + "</div>");
          }
          if (parseData[i].hasOwnProperty("warning")) {
            errorDiv.append("<div class=\"alert alert-warning\">" + parseData[i].warning + "</div>");
          }
          if (parseData[i].hasOwnProperty("info")) {
            errorDiv.append("<div class=\"alert alert-info\">" + parseData[i].info + "</div>");
          }
          errorDivWrapper.show("highlight");
        }
      } else {
        errorDivWrapper.hide();
      }
    }
  } else {
    errorDivWrapper.hide();
  }
}
