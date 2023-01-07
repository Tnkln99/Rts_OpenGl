#include "Log.h"
#include "Game.h"

LogConfig LOG_CONFIG = {};


int main() {
    // Init logging
    LOG_CONFIG.reporting_level = Debug;
    LOG_CONFIG.restart = true;
    if (LOG_CONFIG.restart) {
        Log::restart();
    }

    Game game = Game();

    game.run();

    return 0;
}
