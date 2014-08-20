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
          htmlCode += '<a class="accordion-toggle" data-toggle="collapse-next">\n';
          htmlCode += '<div class="list-group-item-heading">' + presetJson.rulesets[i].name + '</div>\n';
          htmlCode += '</a>\n';
          htmlCode += '<div class="glyphicon glyphicon-resize-vertical ruleMoveButton"></div>\n';
          htmlCode += '<div class="list-group-item-text ruleConfigForm collapse in">';
          htmlCode += '<textarea id="remoterule' + i + '" style="display:none;">{"rules":' + JSON.stringify(presetJson.rulesets[i].rules) + '}</textarea>\n';
          htmlCode += '</div>\n';
          htmlCode += '<a href="#" class="btn btn-success pull-left presetButton" onclick="loadRuleset(\'#remoterule' + i + '\')"><div class="glyphicon glyphicon-arrow-left"></div></a>';
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
 * Populate the #rulesets-local-list
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
//          htmlCode += '<li class="list-group-item presetLi">\n';
//          htmlCode += '<div class="list-group-item-heading">' + presetJson.rulesets[i].name + '</div>\n';
//          htmlCode += '<div class="list-group-item-text ruleConfigForm collapse in">';
//          htmlCode += '<textarea id="localrule' + i + '" style="display:none;">{"rules":' + JSON.stringify(presetJson.rulesets[i].rules) + '}</textarea>\n';
//          htmlCode += '</div>\n';
//          htmlCode += '<a href="#" class="btn btn-success pull-left presetButton" onclick="loadRuleset(\'#localrule' + i + '\')"><div class="glyphicon glyphicon-arrow-left"></div></a>';
//          htmlCode += '<a href="#" class="btn btn-danger pull-right presetButton" onclick="loadRuleset(\'#localrule' + i + '\')"><div class="glyphicon glyphicon-arrow-trash"></div></a>';
//          htmlCode += '</li>\n';


          htmlCode +=
            '<li class="list-group-item">' +
              '<a href="#" onclick="loadRuleset(\'#localrule' + i + '\')">' + presetJson.rulesets[i].name + '</a>' +
              '<textarea id="localrule' + i + '" style="display:none;">{"rules":' + JSON.stringify(presetJson.rulesets[i].rules) + '}</textarea>' +
              '</li>\n';

//              '<button type="button" class="btn btn-default" onclick="loadRuleset(\'#localrule' + i + '\')">' + presetJson.rulesets[i].name +
//              '</button>' +
//              '<button type="button" class="btn btn-danger dropdown-toggle" data-toggle="dropdown">' +
//              '<span class="caret"></span><span class="sr-only">Toggle Dropdown</span></button>' +
//              '<textarea id="localrule' + i + '" style="display:none;">{"rules":' + JSON.stringify(presetJson.rulesets[i].rules) + '}</textarea>' +
//
//
////              '<div class="btn-group">' +
////              '<div class="btn-group">' +
////              '<button type="button" class="btn btn-default glyphicon glyphicon-arrow-left" onclick="loadRuleset(\'#localrule' + i + '\')">' + presetJson.rulesets[i].name + '</button>' +
////              '</div>' +
////              '<button type="button" class="btn btn-danger glyphicon glyphicon-trash"></button>' +
////              '<textarea id="localrule' + i + '" style="display:none;">{"rules":' + JSON.stringify(presetJson.rulesets[i].rules) + '}</textarea>' +
////              '</div>' +
//              '<ul class="dropdown-menu" role="menu">' +
//              '<li><a href="#" onclick="loadRuleset(\'#localrule' + i + '\')">Load</a></li>' +
//              '<li><a class="glyphicon glyphicon-trash" href="#">Delete</a></li>' +
//              '' +
//              '</ul>' +
//              '</li>\n'
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
        rname = $(element).parent().parent().find(".list-group-item-heading").text();

        rmanager.SetCurrentRulesetname(rname);
        setCurrentRulesetName();
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


function callbackClearRules() {
  $('#rules-active').html('');
  setCurrentRulesetName();
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
      '<div class="input-group">' +
      '<label class="checkbox-inline"><input type="checkbox" value="tcp"' + tcp + '> TCP</label>' +
      '</div><div class="input-group">' +
      '<label class="checkbox-inline"><input type="checkbox" value="udp" ' + udp + '> UDP</label>' +
      '</div></div>' +
      '<div class="form-group">' +
      '<div class="input-group">' +
      '<label>Source Address</label>' +
      '<input type="text" class="form-control address" placeholder="Source Address" value="' + addr + '">' +
      '</div>' +
      '<div class="input-group">' +
      '<label>Port</label>' +
      '<input type="text" class="form-control ports" placeholder="Port" value="' + port + '">' +
      '</div>' +
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

function initGui() {
  setCurrentRulesetName();
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
