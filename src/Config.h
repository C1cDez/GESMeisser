#pragma once

#include <string>

#define CONFIG_PSERVER_START_ON "pserver.start.on"
#define CONFIG_PSERVER_PORT "pserver.port"
#define CONFIG_PSERVER_BACKLOG "pserver.backlog"


void loadConfig();
void saveConfig();
std::string& getConfig(const std::string& key);
