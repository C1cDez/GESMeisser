#pragma once

#include <string>

#define CONFIG_ENABLE_IPV6 "enable.ipv6"
#define CONFIG_PSERV_START_ON "pserv.start.on"
#define CONFIG_PSERV_PORT "pserv.port"
#define CONFIG_PSERV_BACKLOG "pserv.backlog"


void loadConfig();
void saveConfig();
std::string& getConfig(const std::string& key);
