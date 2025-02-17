#include "./engine/core/Application.h"
#include "./engine/utils/Logger.h"

int main() {
    Game::Application app;
    app.Run();

    Utils::Logger::Log("Application exiting");
    return 0;
}