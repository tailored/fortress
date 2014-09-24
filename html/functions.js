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
 * File: functions.js                                                     *
 **************************************************************************/

/**
 * Populate the #rulesets-remote-list
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
                    htmlCode += '<div class="list-group-item-heading">' + presetJson.rulesets[i].name + '</div>\n';
                    htmlCode += '<textarea id="remoterule' + i + '" style="display:none;">{"rules":' + JSON.stringify(presetJson.rulesets[i].rules) + '}</textarea>\n';
                    htmlCode += '<div class="glyphicon glyphicon-resize-vertical ruleMoveButton"></div>\n';
                    htmlCode += '<div class="list-group-item-text ruleConfigForm collapse in">';
                    htmlCode += '</div>\n';
                    htmlCode += '<a href="#" class="btn btn-success pull-left presetButton" onclick="loadRuleset(\'#remoterule' + i + '\')"><div class="glyphicon glyphicon-arrow-left"></div></a>';
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
 * @param rulename
 */
function deleteUserRule(rulename) {
    if (rmanager.DeleteUserRuleResponsive(rulename)) {
        if (rulename == $('#headercaption').text()) $('#headercaption').text('unnamed');
        LoadUserRuleSet();
    }
}


/**
 * Populate the #rulesets-local-list
 */
function LoadUserRuleSet() {
    var presetJson = rmanager.LoadUserRules();
    var target = $("#rulesets-local");
    var htmlCode = "";
    if (presetJson.length > 0) {
        presetJson = JSON.parse(presetJson);
        if ((typeof presetJson == 'object')) {
            if (presetJson.hasOwnProperty('rulesets')) {

                for (var i = 0; i < presetJson.rulesets.length; i++) {
                    htmlCode += '<li class="list-group-item presetLi">\n';
                    htmlCode += '<div class="list-group-item-heading">' + presetJson.rulesets[i].name + '</div>\n';
                    htmlCode += '<textarea id="userruleset' + i + '" style="display:none;">{"rules":' + JSON.stringify(presetJson.rulesets[i].rules) + '}</textarea>\n';
                    htmlCode += '<a href="#" class="btn btn-success pull-left presetButton" onclick="loadRuleset(\'#userruleset' + i + '\')"><div class="glyphicon glyphicon-arrow-left"></div></a>';
                    htmlCode += '<a href="#" class="btn btn-danger pull-left trashButton" onclick="deleteUserRule(\'' + presetJson.rulesets[i].name + '\');"><div class="glyphicon glyphicon-trash"></div></a>';
                    htmlCode += '</li>\n';


                    if (presetJson.rulesets[i].name == rmanager.GetCurrentRulesetName()) {
                        $('#rules-active').html('');
                        for (var j = 0; j < presetJson.rulesets[i].rules.length; j++) {
                            insertRule(presetJson.rulesets[i].rules[j].name, presetJson.rulesets[i].rules[j].protocol, presetJson.rulesets[i].rules[j].addr, presetJson.rulesets[i].rules[j].port, true);
                        }
                    }
                }
            }
        }
    }
    target.html(htmlCode);
    $('#countUserRules').html(presetJson.rulesets.length);
    updateDraggables();
}


/**
 * Load a ruleset from a given html element
 */
function loadRuleset(element) {
    if (confirm("This will replace your current ruleset! Are you sure?")) {

        rulesJson = JSON.parse($(element).val());
        if ((typeof rulesJson) == 'object') {
            if (rulesJson.hasOwnProperty('rules')) {
                $('#rules-active').html('');
                for (var i = 0; i < rulesJson.rules.length; i++) {
                    insertRule(rulesJson.rules[i].name, rulesJson.rules[i].protocol, rulesJson.rules[i].addr, rulesJson.rules[i].port, true);
                }
                updateDraggables();
                rname = $(element).parent().find(".list-group-item-heading").text();

                rmanager.SetCurrentRulesetname(rname);
                setCurrentRulesetName();
                mwindow.saveAs(rname);
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

/**
 *
 */
function callbackClearRules() {
    $('#rules-active').html('');
    setCurrentRulesetName();
}

/**
 * @param name
 * @param protocol
 * @param addr
 * @param port
 * @param collapsed
 * @param list
 */
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
            '<div class="list-group-item-text ruleConfigForm collapse' + col + '">' +
            '<form class="ruleform">' +
            '<div class="form-group input-group">' +
            '<label class="input-group-addon"><div class="formLabel">Name</div></label>' +
            '<input type="text" name="rulename" class="form-control rulename" placeholder="Rule Name" value="' + name + '">' +
            '</div>' +
            '<div class="input-group form-group">' +
            '<label class="input-group-addon"><div class="formLabel">Source Address</div></label>' +
            '<input type="text" name="sourceaddress" class="form-control address" placeholder="Any" value="' + addr + '">' +
            '</div>' +
            '<div class="form-group input-group">' +
            '<label class="input-group-addon"><div class="formLabel">Port</div></label>' +
            '<input type="text" name="ports" class="form-control ports" placeholder="All" value="' + port + '">' +
            '</div>' +
            '<div class="form-group input-group inputcheckbox">' +
            '<div class="checkbox">' +
            '<label class="checkbox-inline"><input type="checkbox" name="protocol[]" value="tcp"' + tcp + '> TCP</label>' +
            '</div>' +
            '<div class="checkbox">' +
            '<label class="checkbox-inline"><input type="checkbox" name="protocol[]" value="udp" ' + udp + '> UDP</label>' +
            '</div>' +
            '</div>&nbsp;&nbsp;' +
            '<button type="submit" class="btn btn-primary saverule float-right">Save</button>' +
            '<button type="button" class="btn btn-danger delrule float-right cbtn">Delete Rule</button>' +
            '<textarea name="json" style="display:none;">' + JSON.stringify(rulejson) + '</textarea>' +
            '</form></div>' +
            '</li>');

    validateRules();
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
            $(this).parent().parent().parent().hide("puff", null, 200, function () {
                $(this).remove();
              rulesChanged();
            });

        });
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
        rulesChanged();
        return false;
        });

}

/**
 *
 */
function setCurrentRulesetName() {
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

/**
 *
 */
function initGui() {
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
        validateRules();
    });

    validateSettings();
    getSettings();
}


function rulesChanged() {
  rf = $('.ruleform');
  rf.data('bootstrapValidator').validate();
  rmanager.setIsDeployAble(rf.data('bootstrapValidator').isValid());
}


function validateRules() {
    $('.ruleform').bootstrapValidator({
        feedbackIcons: {
            valid: 'glyphicon glyphicon-ok',
            invalid: 'glyphicon glyphicon-remove',
            validating: 'glyphicon glyphicon-refresh'
        },
        fields: {
            rulename: {
                message: 'The rule name is not valid',
                validators: {
                    notEmpty: {
                        message: 'The rule name is required and cannot be empty'
                    },
                    stringLength: {
                        min: 3,
                        max: 50,
                        message: 'The rule name must be more than 3 and less than 50 characters long'
                    }
                }
            },
            sourceaddress: {
                message: 'The source address is not valid',
                validators: {
                    ip: {
                        ipv4: true,
                        ipv6: false,
                        message: 'The source address must be an ip address'
                    }
                }
            },
            ports: {
                message: 'The port is not valid',
                validators: {
                    notEmpty: {
                        message: 'Port must not be empty'
                    },
                    regexp: {
                        message: 'The port is invalid',
                      regexp: /^0*(?:6553[0-5]|655[0-2][0-9]|65[0-4][0-9]{2}|6[0-4][0-9]{3}|[1-5][0-9]{4}|[1-9][0-9]{1,3}|[0-9])(,0*(?:6553[0-5]|655[0-2][0-9]|65[0-4][0-9]{2}|6[0-4][0-9]{3}|[1-5][0-9]{4}|[1-9][0-9]{1,3}|[0-9]))*$/
                    }


                }
            },
            'protocol[]': {
                message: 'The protocol is not valid',
                validators: {
                    choice: {
                        min: 1,
                        message: 'Please select a protocol'
                    }
                }

            }

        }
    }).bootstrapValidator('validate');
  rulesChanged();
}
