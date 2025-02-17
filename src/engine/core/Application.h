#ifndef APPLICATION_H
#define APPLICATION_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>

#include "../graphics/MeshStatic.h"
#include "../graphics/MeshDynamic.h"

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

    // Temporary, for development purposes
    std::unique_ptr<Graphics::MeshStatic> m_meshStatic;
    std::unique_ptr<Graphics::MeshDynamic> m_meshDynamic;
    Graphics::Quad m_quads[2];


    bool m_applicationShouldTerminate = false;

    GLuint m_shaderProgram = 0;
    GLFWwindow* m_window = nullptr;
};

} // Game

#endif //APPLICATION_H
