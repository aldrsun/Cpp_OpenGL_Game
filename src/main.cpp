#include "game/Game.h"
#include "utils/Logger.h"

int main() {

    Game::Game *g = new Game::Game();
    
    g->Run();
    
    Utils::Logger::Log("Application exiting");
}