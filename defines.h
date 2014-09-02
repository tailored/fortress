#ifndef DEFINES_H
#define DEFINES_H

#define FORTRESS_ORGANISATION "ipv6Watch"
#define FORTRESS_ORGANISATION_DOMAIN "https://github.com/ipv6Watch/fortress"
#define FORTRESS_APPLICATION "Fortress"
#define FORTRESS_GITHUB_STASHLIST_URL "https://raw.githubusercontent.com/ipv6Watch/fortress-preset-stash/master/stashes.json"

#define FORTRESS_STASHES_RULES_FILENAME "rules.json"
#define FORTRESS_STASHES_PRESETS_FILENAME "presets.json"

#define FORTRESS_WEBVIEW_STARTPAGE "qrc:/html/html/index.html"

#define FORTRESS_ERROR_CHECK_ENTRIES "<b><a href=\"#settings\" data-toggle=\"tab\" onclick=\"$('#settingsTabLink').click();\">Please check entries or run autodetect!</a></b>"
#define FORTRESS_ERROR_SUDOPROVIDER_NOT_INSTALLED "could not find installed sudoproviders, please install <i>gksu</i> or <i>kdesudo</i> or enter a path manually"
#define FORTRESS_ERROR_SUDOPROVIDER_NOT_FOUND "path sudoprovider you entered could not be found!"
#define FORTRESS_ERROR_SUDOPROVIDER_NOT_EXECUTABLE "path sudoprovider you entered is not executable!"
#define FORTRESS_ERROR_IPTABLES_NOT_INSTALLED "could no find iptables installation, please install iptables or enter a path manually"
#define FORTRESS_ERROR_IPTABLES_NOT_FOUND "path to iptables not found!"
#define FORTRESS_ERROR_IPTABLES_NOT_EXECUTABLE "path to iptables is not executable!"

#define FORTRESS_KEYWORD_ERROR "error"
#define FORTRESS_KEYWORD_WARNING "warning"
#define FORTRESS_KEYWORD_INFO "info"
#define FORTRESS_KEYWORD_USERFEEDBACK "userfeedback"
#define FORTRESS_KEYWORD_NETWORK_INTERFACES_LIST "networkInterfaces"
#define FORTRESS_KEYWORD_NETWORK_INTERFACES_INTERFACE_NAME "networkInterfaceName"
#define FORTRESS_KEYWORD_NETWORK_INTERFACES_ALL_INTERFACES "All"

#define FORTRESS_GENERATOR_REPLACE_TOKEN "%%%%TEMPLATEDATA%%%%"

#define FORTRESS_RULES_MANAGER_SAVE_OK 0
#define FORTRESS_RULES_MANAGER_SAVE_RULE_EXISTS 1
#define FORTRESS_RULES_MANAGER_SAVE_RULE_ACCESS_DENIED 2
#define FORTRESS_RULES_MANAGER_SAVE_RULE_DOES_NOT_EXIST 3
#define FORTRESS_RULES_MANAGER_RULES_REL_PATH "/rules/";
#define FORTRESS_RULES_MANAGER_RULES_REL_PATH_USER_PRESETS "/rules/userpresets/"
#define FORTRESS_RULES_BOOT_DEPLOYMENT_PATH "/opt/fortress/"

#define FORTRESS_DEFAULT_RULESET_NAME "unnamed"
#define FORTRESS_RULESET_SAVE_DIALOG_TITLE "Ruleset Name"
#define FORTRESS_RULESET_SAVE_DIALOG_TEXT "Please enter a name for the ruleset"
#define FORTRESS_RULESET_SAVE_OVERWRITE_WARNING_TITLE "Overwrite?"
#define FORTRESS_RULESET_SAVE_OVERWRITE_WARNING_TEXT "The selected filename already exists. Overwrite?"

#define FORTRESS_RULESET_CLEAR_TEXT "The current ruleset will be purged if you proceed!"
#define FORTRESS_RULESET_CLEAR_TITLE "Warning"

#define FORTRESS_SUPPORTED_OSS "Gentoo  Debian  Arch  Mint"

#define FORTRESS_DIALOG_EXPORT "Export firewallscript"

#define FORTRESS_DIALOG_TITLE_ARE_YOUR_SURE "Are you sure?"
#define FORTRESS_DIALOG_TEXT_DEPLOY_SYSTEM "This will deploy the firewallrules below to your System. Are you sure?"
#define FORTRESS_DIALOG_TEXT_DEPLOY_SYSTEM_BOOT "This will deploy the firewallrules below to the boot process of your System. Are you sure?"

#define FORTRESS_DIALOG_TITLE_CRITICAL_ERROR "Critical error"
#define FORTRESS_DIALOG_TEXT_OS_UNSUPPORTED "Your operating system is not supported! We are sorry.\nYou will not be able to deploy the configuration, however\nyou may create firewallscripts and export them as shell scripts."

#define FORTRESS_DIALOG_TEXT_DELETE_RULE_PART1 "This will delete the ruleset \""
#define FORTRESS_DIALOG_TEXT_DELETE_RULE_PART2 "\" permanently. Are you sure?"

#endif // DEFINES_H
