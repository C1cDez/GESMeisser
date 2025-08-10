#include <iostream>

#include "Config.h"
#include "Network.h"


int commandLineMain(int argc, char* argv[]);
void programMain();


int main(int argc, char* argv[])
{
    if (argc > 1)
        return commandLineMain(argc, argv);
    else
    {
        programMain();
        return 0;
    }
}

int commandLineMain(int argc, char* argv[])
{
    const char* command = argv[1];
    if (!strcmp("--help", command) || !strcmp("-h", command))
    {
        std::printf(
            "\nGES Meisser CLI:\n"
            "Usage:\n\n"
            "\t-h, --help\t\t\t\tPrints this manual\n"
            "\t-c, --config [key] [value]\t\tEdits config\n"
        );
    }
    else if (!strcmp("--config", command) || !strcmp("-c", command))
    {
        if (argc < 4)
        {
            std::printf("Usage:\n\t%s [key] [value]\n", command);
            return 1;
        }
        const char* key = argv[2];
        const char* value = argv[3];
        loadConfig();
        getConfig(key) = value;
        saveConfig();
        std::printf("Set: %s=%s\n", key, value);
    }
    else
    {
        std::printf("Unrecognized command: %s\n", argv[1]);
        return 1;
    }
    return 0;
}

void programMain()
{
    std::printf("Starting program\n");
    if (startupWS2())
    {
        std::printf("WSA Failed\n");
        return;
    }

    loadConfig();

    Peer& peer = Peer::thisPeer();
    if (int status = peer.init())
    {
        std::printf("Peer initialization failed: CODE=%d\n", status);
        return;
    }
    peer.run();
    peer.close();

    saveConfig();
}
