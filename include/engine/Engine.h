#ifndef ENGINE_H
#define ENGINE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>

#include "graphics/MeshStatic.h"
#include "graphics/MeshDynamic.h"

namespace Engine {

class Engine {
public:
    Engine();
    
    void Render();
    void Update();
    void Shutdown();

    bool GetEngineShouldTerminate() const;
private:
    int m_Initialize();

    // Temporary, for development purposes
    std::unique_ptr<Graphics::MeshStatic> m_meshStatic;
    std::unique_ptr<Graphics::MeshDynamic> m_meshDynamic;
    Graphics::Quad m_quads[2];


    bool m_engineShouldTerminate = false;

    GLuint m_shaderProgram = 0;
    GLFWwindow* m_window = nullptr;
};

} // namespace Engine

#endif //ENGINE_H
