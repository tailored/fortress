/**
 * Created by chaser on 2/24/14.
 */
function getSettings() {
  //var ifaces = JSON.parse(smanager.getNetWorkInterfaces());
  //var currentIface = smanager.getValue("settings/interface");
  /*
  if (ifaces.hasOwnProperty("networkInterfaces")) {
    retVal = "<select name=\"settings-networkinterfacelist\" id=\"settings-networkinterfacelist\" class=\"form-control\">";
    for (var i = 0; i < ifaces.networkInterfaces.length; i++) {
      retVal += "<option value=\"" + ifaces.networkInterfaces[i].networkInterfaceName + "\"";
      if (currentIface == ifaces.networkInterfaces[i].networkInterfaceName) retVal += " selected=\"selected\" ";
      retVal += ">" + ifaces.networkInterfaces[i].networkInterfaceName + "</option>"
    }
    retVal += "</select>";
    $("#settings-networkinterface").html(retVal);
  }
  */
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
  var checkme = smanager.getValue("settings/fetchstashes") == "true";
  $("#settings-fetchstashes").prop("checked", checkme);
}

function setSettings() {
  var selectedStashUrl = $("#settings-stashurl");
  //smanager.setValue("settings/interface", $("#settings-networkinterfacelist").val());
  smanager.setValue("settings/sudoprovider", $("#settings-sudoprovider").val());
  smanager.setValue("settings/iptables", $("#settings-iptables").val());
  smanager.setValue("settings/stashurl", selectedStashUrl.val());
  smanager.setValue("settings/stashname", selectedStashUrl.find("option:selected").text());
  smanager.setValue("settings/fetchstashes", $("#settings-fetchstashes").is(":checked"));
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
      smanager.setValue("settings/fetchstashes", "true");
    }
  }
  validateSettings();
  getSettings();
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

/**
 *
 * @param sourceDivObject
 * @param ruleType
 */
function onRuleDrop() {
  //var form = callToSomeCPPFunctionWhichProvidesFormData(ruleType);
  // - form target will trigger another c++ function to store form value to ruleset according to ruletype
  // - ruletype can be either tcp, udp or icmp
  // - i'll implement this tomorrow i am tired now :)
  $(sourceDivObject).html("i will paste the form here acording to type");
}