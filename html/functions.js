/**
 * Created by chaser on 2/24/14.
 */
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
  var checkme = smanager.getValue("settings/fetchstashes") == "true";
  $("#settings-fetchstashes").prop("checked", checkme);
  validateSettings();
}

function setSettings() {
  var selectedStashUrl = $("#settings-stashurl");
  smanager.setValue("settings/sudoprovider", $("#settings-sudoprovider").val());
  smanager.setValue("settings/iptables", $("#settings-iptables").val());
  smanager.setValue("settings/stashurl", selectedStashUrl.val());
  smanager.setValue("settings/stashname", selectedStashUrl.find("option:selected").text());
  smanager.setValue("settings/fetchstashes", $("#settings-fetchstashes").is(":checked"));
  getSettings();
  validateSettings();
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
    validateSettings();
    getSettings();
  } else {
  }
}

function validateSettings() {
  var error = smanager.validateSettings();
  var errorDiv = $("#settingsError");
  if (error.length > 0) {
    errorDiv.html(error);
    errorDiv.show("highlight");
  } else {
    errorDiv.html("");
    errorDiv.hide();
  }
}