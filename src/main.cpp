#include "core/Application.h"
#include "utils/Logger.h"

int main() {
    Game::Application app;
    app.Run();

    Utils::Logger::Log("Application exiting");
    return 0;
}