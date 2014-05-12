/**
 * Created by chaser on 2/24/14.
 */
function getSettings() {
  $("#settings-sudoprovider").val(smanager.getValue("settings/sudoprovider"));
  $("#settings-iptables").val(smanager.getValue("settings/iptables"));
  validateSettings();
}

function setSettings() {
  smanager.setValue("settings/sudoprovider", $("#settings-sudoprovider").val());
  smanager.setValue("settings/iptables", $("#settings-iptables").val());
  getSettings();
  validateSettings();
}

function autoDetectSettings() {
  smanager.initConfig();
  validateSettings();
  getSettings();
}

function validateSettings() {
  var error = smanager.validateSettings();
  var errorDiv = $("#settingsError");
  if(error.length > 0) {
    errorDiv.html(error);
    errorDiv.show("highlight");
  } else {
   errorDiv.html("");
   errorDiv.hide();
  }
}

function readyFunc() {
  getSettings();
}