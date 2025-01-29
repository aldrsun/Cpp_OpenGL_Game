#ifndef APPLICATION_H
#define APPLICATION_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>

#include "../graphics/Mesh.h"

namespace Game {

class Application {
public:
    Application();
    void Run();

private:
    int m_Initialize();
    int m_GenerateGameObjects();
    void m_Update();
    void m_Render();
    void m_Shutdown();

    std::unique_ptr<Graphics::Mesh> m_mesh;

    bool m_applicationShouldTerminate = false;

    GLuint m_shaderProgram = 0;
    GLFWwindow* m_window = nullptr;
};

} // Game

#endif //APPLICATION_H
