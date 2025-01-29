#ifndef APPLICATION_H
#define APPLICATION_H

#include "../graphics/Mesh.h"

namespace Game {

class Application {
public:
    Application();
    void Run();

private:
    int Initialize();
    int GenerateGameObjects();
    void Update();
    void Render();
    void Shutdown();

    Graphics::Mesh mesh;

    bool application_should_terminate = false;
};

} // Engine

#endif //APPLICATION_H
