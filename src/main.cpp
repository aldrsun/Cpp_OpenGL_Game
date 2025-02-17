#include "./game/Application.h"
#include "./engine/utils/Logger.h"

int main() {
    Game::Run();

    Engine::Utils::Logger::Log("Application exiting");
    return 0;
}