#include "engine/Application.h"
#include "utils/Logger.h"

int main() {
    Game::Run();

    Engine::Utils::Logger::Log("Application exiting");
    return 0;
}