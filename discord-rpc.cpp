#include <iostream>
#include "include/discord_rpc.h"
#include <cstring>
#include <limits>
#include <chrono>
#include <thread>
using namespace std;

static char APPLICATION_ID[18] = {};

static void updateDiscordPresence(char *details, char *state, char *largeImageKey, char *smallImageKey, int64_t startTimestamp, int64_t endTimestamp)
{
    DiscordRichPresence discordPresence;

    memset(&discordPresence, 0, sizeof(discordPresence));

    discordPresence.state = state;
    discordPresence.details = details;

    if (startTimestamp != 0)
        discordPresence.startTimestamp = startTimestamp;

    if (endTimestamp != 0)
        discordPresence.endTimestamp = endTimestamp;

    discordPresence.largeImageKey = largeImageKey;
    discordPresence.smallImageKey = smallImageKey;
    discordPresence.instance = 0;

    Discord_UpdatePresence(&discordPresence);
}

int main(int argc, char *argv[])
{
    char *details = {};
    char *state = {};

    char *largeImageKey = {};
    char *smallImageKey = {};

    int64_t startTimestamp = 0;
    int64_t endTimestamp = 0;

    bool verbose = false;

    for (int i = 0; i < argc; i++)
    {
        std::string arg = argv[i];
        cout << arg << endl;
        if (arg == "--application-id" || arg == "--app" || arg == "-a")
            for (int j = 0; j < 19; ++j)
                APPLICATION_ID[j] = argv[i + 1][j];

        else if (arg == "--details" || arg == "-d")
            details = argv[i + 1];

        else if (arg == "--state" || arg == "-s")
            state = argv[i + 1];

        else if (arg == "--large-image-key" || arg == "-li")
            largeImageKey = argv[i + 1];

        else if (arg == "--small-image-key" || arg == "-si")
            smallImageKey = argv[i + 1];

        else if (arg == "--start-timestamp" || arg == "-st")
            startTimestamp = stoi(argv[i + 1]);

        else if (arg == "--end-timestamp" || arg == "-et")
            endTimestamp = stoi(argv[i + 1]);

        else if (arg == "--verbose" || arg == "-v")
            verbose = true;
    }

    if (verbose)
    {
        cout << "  Application ID: " << APPLICATION_ID << endl;
        cout << "         Details: " << details << endl;
        cout << "           State: " << state << endl;
        cout << "      Large icon: " << (largeImageKey ? largeImageKey : "<none>") << endl;
        cout << "      Small icon: " << (smallImageKey ? smallImageKey : "<none>") << endl;
        cout << " Begin timestamp: " << startTimestamp << endl;
        cout << "   End timestamp: " << endTimestamp << endl;
    }

    DiscordEventHandlers handlers;

    memset(&handlers, 0, sizeof(handlers));

    Discord_Initialize(APPLICATION_ID, &handlers, 1, NULL);

    updateDiscordPresence(details, state, largeImageKey, smallImageKey, startTimestamp, endTimestamp);
    
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        system("if pgrep -x \"GenshinImpact.e\" > /dev/null; then echo \"Running\";else if pgrep -x \"an-anime-game-l\" > /dev/null; then echo \"Launcher Running\" > /dev/null ;else killall discord;fi; fi");
    };
    return 0;
}
