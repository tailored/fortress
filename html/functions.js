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
}

function setSettings() {
  var selectedStashUrl = $("#settings-stashurl");
  //smanager.setValue("settings/interface", $("#settings-networkinterfacelist").val());
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
  //alert("on drop function triggered");
}

/**
 *
 */
function callBackUpdatePresets() {
  var presetJson = rmanager.LoadStashPresets();
  var target = $("#lst-presets");
  if (presetJson.length > 0) {
    presetJson = JSON.parse(presetJson);
    if ((typeof presetJson == 'object')) {
      if (presetJson.hasOwnProperty('rulesets')) {
        var htmlCode = "";
        for (var i = 0; i < presetJson.rulesets.length; i++) {
          htmlCode += '<li class="list-group-item presetLi">\n';
          htmlCode += '<a class="accordion-toggle" data-toggle="collapse-next">\n';
          htmlCode += '<div class="list-group-item-heading">' + presetJson.rulesets[i].name + '</div>\n';
          htmlCode += '</a>\n';
          htmlCode += '<div class="glyphicon glyphicon-resize-vertical ruleMoveButton"></div>\n';
          htmlCode += '<div class="list-group-item-text ruleConfigForm collapse in">';
          htmlCode += '<textarea id="presetContent' + i + '" style="display:none;">{"rules":' + JSON.stringify(presetJson.rulesets[i].rules) + '}</textarea>\n';
          htmlCode += '</div>\n';
          htmlCode += '<a href="#" class="btn btn-success pull-left presetButton" onclick="deployPreset(\'#presetContent' + i + '\')"><div class="glyphicon glyphicon-arrow-left"></div></a>';
          htmlCode += '</li>\n';
        }
        target.html(htmlCode);
        $('#countPresets').html(presetJson.rulesets.length);
        updateDraggables();
      }
    }
  }
}

/**
 *
 * @param preset
 */
function deployPreset(preset) {
  if(confirm("This will replace your current ruleset! Are you sure?")) {
    alert("make it so");
    // ruleset json can be extracted from $(preset).val();
  }
}

/**
 *
 */
function callBackUpdateRules() {
  var rulesJson = rmanager.LoadStashRules();
  var target = $('#stashRulesContent');
  if (rulesJson.length > 0) {
    rulesJson = JSON.parse(rulesJson);
    if ((typeof rulesJson) == 'object') {
      if (rulesJson.hasOwnProperty('rules')) {
        var htmlCode = "";
        for (var i = 0; i < rulesJson.rules.length; i++) {
          htmlCode += '<li class="list-group-item">\n';
          htmlCode += '<a class="accordion-toggle" data-toggle="collapse-next">\n';
          htmlCode += '<div class="list-group-item-heading">' + rulesJson.rules[i].name + '</div>\n';
          htmlCode += '</a>\n';
          htmlCode += '<div class="glyphicon glyphicon-resize-vertical ruleMoveButton"></div>\n';
          htmlCode += '<div class="list-group-item-text ruleConfigForm collapse in">\n';
          htmlCode += '<button type="button" class="btn btn-danger delrule glyphicon glyphicon-fire"></button>\n';
          htmlCode += '</div>\n';
          htmlCode += '</li>\n';
        }
        target.html(htmlCode);
        $('#countCollapseStashRules').html(rulesJson.rules.length);
        updateDraggables();
      }
    }
  }
}

/**
 *
 */
function updateDraggables() {
  $("#lst-userpresets li, #lst-rules li, #stashRulesContent li").draggable({
    connectToSortable: "#lst-activerules",
    helper: "clone",
    revert: "invalid"
  }).disableSelection();
  $(".delrule")
    .click(function() {
      $(this).parent().parent().hide("puff", null, 400, function()
      {
        $(this).remove();
      });

  })
}


function returnCurrentConfig() {
  return "<<< current config >>>";
}