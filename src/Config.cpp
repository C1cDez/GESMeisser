#include "Config.h"

#include <fstream>
#include <map>

#define CONFIG_FILE_NAME "config"


static std::map<std::string, std::string> sConfigMap;

void setConfigIfNone(const std::string& key, const std::string& value);
void analyzeConfig();


void loadConfig()
{
    std::ifstream file{ CONFIG_FILE_NAME };
    if (!file.is_open()) std::printf("No file to load the config from was found\n");

    std::string line{};
    while (std::getline(file, line))
    {
        size_t equals = line.find('=');
        std::string key = line.substr(0, equals), value = line.substr(equals + 1);
        sConfigMap[key] = value;
    }
    file.close();

    analyzeConfig();
}

void saveConfig()
{
    std::ofstream file{ CONFIG_FILE_NAME };
    for (const auto& entry : sConfigMap)
        file << entry.first << "=" << entry.second << "\n";
    file.close();
}

std::string& getConfig(const std::string& key)
{
    return sConfigMap[key];
}

void setConfigIfNone(const std::string& key, const std::string& value)
{
    if (sConfigMap.find(key) == sConfigMap.end())
        sConfigMap[key] = value;
}
void analyzeConfig()
{
    setConfigIfNone(CONFIG_PSERVER_START_ON, "0.0.0.0");
    setConfigIfNone(CONFIG_PSERVER_PORT, "216");
    setConfigIfNone(CONFIG_PSERVER_BACKLOG, "128");
}
