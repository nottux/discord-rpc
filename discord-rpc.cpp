#include <iostream>
#include "include/discord_rpc.h"
#include <cstring>
#include <limits>
#include <chrono>
#include <thread>

static char APPLICATION_ID[18] = {};

static void updateDiscordPresence(char *details, char *state, char *largeImageKey, char *smallImageKey, int64_t startTimestamp, int64_t endTimestamp)
{
    DiscordRichPresence *discordPresence=new DiscordRichPresence;
    //this memset gave me so much pain someone please find dennis ritchie and beat the shit out of him
    memset(discordPresence, 0, sizeof(&discordPresence));
    
    discordPresence->state = state;
    discordPresence->details = details;

    if (startTimestamp != 0)
        discordPresence->startTimestamp = startTimestamp;

    if (endTimestamp != 0)
        discordPresence->endTimestamp = endTimestamp;

    discordPresence->largeImageKey = largeImageKey;
    discordPresence->smallImageKey = smallImageKey;
    discordPresence->instance = 0;

    Discord_UpdatePresence(discordPresence);
}

int main(int argc, char *argv[])
{
    char *details = {}; 
    char *state= {}; 
    
    char *largeImageKey ={};
    char *smallImageKey ={}; 
    
    
    int64_t startTimestamp = 0;
    int64_t endTimestamp = 0;

    bool verbose = false;

    for (int i = 0; i < argc; i++)
    {
        std::string arg = argv[i];
        std::cout << arg << std::endl;
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
            startTimestamp = std::stoi(argv[i + 1]);

        else if (arg == "--end-timestamp" || arg == "-et")
            endTimestamp = std::stoi(argv[i + 1]);

        else if (arg == "--verbose" || arg == "-v")
            verbose = true;
    }

    if (verbose)
    {
        std::cout << "  Application ID: " << APPLICATION_ID << std::endl;
        std::cout << "         Details: " << details << std::endl;
        std::cout << "           State: " << state << std::endl;
        std::cout << "      Large icon: " << (largeImageKey ? largeImageKey : "<none>") << std::endl;
        std::cout << "      Small icon: " << (smallImageKey ? smallImageKey : "<none>") << std::endl;
        std::cout << " Begin timestamp: " << startTimestamp << std::endl;
        std::cout << "   End timestamp: " << endTimestamp << std::endl;
    }

    DiscordEventHandlers handlers;

    memset(&handlers, 0, sizeof(handlers));

    Discord_Initialize(APPLICATION_ID, &handlers, 1, NULL);

    updateDiscordPresence(details, state, largeImageKey, smallImageKey, startTimestamp, endTimestamp);
    printf("called rpc update");
    for(;;)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        system("if pgrep -x \"GenshinImpact.e\" > /dev/null; then echo \"Running\";else if pgrep -x \"an-anime-game-l\" > /dev/null; then echo \"Launcher Running\";else killall discord-rpc;fi; fi");
    };

    return 0;
}
