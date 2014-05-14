#ifndef DEFINES_H
#define DEFINES_H

#define FORTRESS_ORGANISATION "ipv6Watch"
#define FORTRESS_ORGANISATION_DOMAIN "https://github.com/ipv6Watch/fortress"
#define FORTRESS_APPLICATION "Fortress"
#define FORTRESS_GITHUB_STASHLIST_URL "https://raw.githubusercontent.com/ipv6Watch/fortress-preset-stash/master/stashes.json"

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

#endif // DEFINES_H
