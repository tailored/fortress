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

    var target = $("#rulesets-remote");
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
                    htmlCode += '<a href="#" class="btn btn-success pull-left presetButton" onclick="loadRuleset(\'#presetContent' + i + '\')"><div class="glyphicon glyphicon-arrow-left"></div></a>';
                    htmlCode += '</li>\n';

                    //insertRule(rulesJson.rules[i].name, {"tcp":1, "udp":1}, "127.0.0.1", 0, 0, true, 2);
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
 */
function LoadUserRuleSet() {
  var presetJson = rmanager.LoadUserRules();
  var target = $("#rulesets-local");

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
          htmlCode += '<a href="#" class="btn btn-success pull-left presetButton" onclick="loadRuleset(\'#presetContent' + i + '\')"><div class="glyphicon glyphicon-arrow-left"></div></a>';
          htmlCode += '</li>\n';

          //insertRule(rulesJson.rules[i].name, {"tcp":1, "udp":1}, "127.0.0.1", 0, 0, true, 2);
        }
        target.html(htmlCode);
        $('#countUserRules').html(presetJson.rulesets.length);
        updateDraggables();

      }
    }
  }
}


/**
 *
 * @param preset
 */
function loadRuleset(preset) {
    if (confirm("This will replace your current ruleset! Are you sure?")) {
        rulesJson = JSON.parse($(preset).val());
        if ((typeof rulesJson) == 'object') {
            if (rulesJson.hasOwnProperty('rules')) {
                $('#rules-active').html('');
                for (var i = 0; i < rulesJson.rules.length; i++) {
                    insertRule(rulesJson.rules[i].name, rulesJson.rules[i].protocol, rulesJson.rules[i].addr, rulesJson.rules[i].port, true);
                }
                updateDraggables();
            }
        }
    }
}

/**
 *
 */
function callBackUpdateRules() {
    var rulesJson = rmanager.LoadStashRules();
    var target = $('#rules-remote');
    if (rulesJson.length > 0) {
        rulesJson = JSON.parse(rulesJson);
        if ((typeof rulesJson) == 'object') {
            if (rulesJson.hasOwnProperty('rules')) {
                $('#rules-remote').html('');
                for (var i = 0; i < rulesJson.rules.length; i++) {
                    insertRule(rulesJson.rules[i].name, rulesJson.rules[i].protocol, rulesJson.rules[i].addr, rulesJson.rules[i].port, true, 4);
                }
                $('#countCollapseStashRules').html(rulesJson.rules.length);
                updateDraggables();
            }
        }
    }
}


function insertRule(name, protocol, addr, port, collapsed, list) {
    tcp = (protocol["tcp"]) ? " checked" : "";
    udp = (protocol["udp"]) ? " checked" : "";
    col = (!collapsed ? " in" : "");
    port = (port ? port : 0);
    addr = (addr ? addr : "");
    var rulejson = {"name": name, "protocol": protocol, "port": port, "addr": addr};

    if (list == 1) {
        target = '#rules-user';
    } else if (list == 2) {
        target = '#rulesets-remote';
    } else if (list == 3) {
        target = '#rulesets-local';
    } else if (list == 4) {
        target = '#rules-remote';

    } else {
        target = '#rules-active';
    }

    $(target).append(
        '<li class="list-group-item"><a class="accordion-toggle" data-toggle="collapse-next">' +
            '<div class="list-group-item-heading">' + name + '</div></a>' +
            '<div class="ruleMoveButton"><span class="glyphicon glyphicon-resize-vertical"></span></div>' +
            '<div class="list-group-item-text ruleConfigForm collapse' + col + '"><form role="form">' +
            '<div class="form-group">' +
            '<input type="text" class="form-control rulename" placeholder="Rule Name" value="' + name + '">' +
            '</div>' +
            '<div class="form-group">' +
            '<label class="checkbox-inline"><input type="checkbox" value="tcp"' + tcp + '> TCP</label>' +
            '<label class="checkbox-inline"><input type="checkbox" value="udp" ' + udp + '> UDP</label>' +
            '</div>' +
            '<div class="form-group">' +
            '<input type="text" class="form-control address" placeholder="Source Address" value="' + addr + '">' +
            '<input type="text" class="form-control ports" placeholder="Ports" value="' + port + '">' +
            '</div>' +
            '<button type="button" class="btn btn-primary saverule">Save</button>' +
            '<button type="button" class="btn btn-danger delrule">Delete Rule</button>' +
            '<textarea name="json" style="display:none;">' + JSON.stringify(rulejson) + '</textarea>' +
            '</form></div>' +
            '</li>');
}


/**
 *
 */
function updateDraggables() {
    $("#rules-user li, #rules-remote li").draggable({
        connectToSortable: "#rules-active",
        helper: "clone",
        revert: "invalid"
    }).disableSelection();
    $(".delrule")
        .click(function () {
            $(this).parent().parent().parent().hide("puff", null, 400, function () {
                $(this).remove();
            });

        })
    $(".saverule")
        .click(function () {
            $container = $(this).parent().parent().parent();
            $jsonstore = $(this).parent().find("textarea[name=json]");
            $container.find('.collapse').collapse('toggle');
            form_title = $(this).parent().find("input.rulename").val();
            form_tcp = $(this).parent().find("input[type=checkbox][value=tcp]").is(':checked');
            form_udp = $(this).parent().find("input[type=checkbox][value=udp]").is(':checked');
            form_port = $(this).parent().find("input.ports").val();
            form_addr = $(this).parent().find("input.address").val();

            if (form_title) {
                $container.find(".list-group-item-heading").text(form_title);
            }

            var protocoljson = {"tcp": form_tcp, "udp": form_udp};
            var rulejson = {"name": form_title, "protocol": protocoljson, "port": form_port, "addr": form_addr};
            $jsonstore.text(JSON.stringify(rulejson));
        })
}


function setRuleName() {
  $('#headercaption').html(rmanager.GetCurrentRulesetName());
  LoadUserRuleSet();
}

/*
 Returns the current Rules as JSON String
 */
function getCurrentRules() {
    var listItems = $("#rules-active li");
    var ruleList = [];
    listItems.each(function (idx, li) {
        ruleString = $(li).find("textarea[name=json]").val();
        ruleList.push(ruleString);
    });
    return('[' + ruleList + ']');
}

function initGui() {
    setRuleName();
    insertRule("Example Rule 1", {"tcp": true, "udp": true}, "", 0, true, 0);
    insertRule("Example Rule 2", {"tcp": true, "udp": true}, "127.0.0.1", 0, true, 0);
    insertRule("Example Rule 3", {"tcp": true, "udp": false}, "127.0.0.1", 0, true, 0);
    insertRule("TCP/UDP", {"tcp": true, "udp": true}, '', '', false, 1);
    $('#toolTipPresets').tooltip();
    $('#toolTipUserPresets').tooltip();
    $('#toolTipRules').tooltip();

    $("#rules-active")
        .sortable({
            items: "li:not(.list-group-item-info)",
            distance: 10,
            handle: ".ruleMoveButton",
            stop: function (event, ui) {
                updateDraggables();
            }
        }).disableSelection();

    $('#rules-active').on('click.collapse-next.data-api', '[data-toggle=collapse-next]', function (e) {

        var $target = $(this).parent().find('.collapse');
        $target.collapse('toggle');
    });

    validateSettings();
    if (smanager.getValue("settings/firstrun").length < 1) {
        alert("Fortress has not been configured yet, please go to settings and run autodetect or configure manually!");
        $("#settingsTab").highlight();
    }
    getSettings();
}