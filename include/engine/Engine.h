#ifndef ENGINE_H
#define ENGINE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>

#include "engine/Renderer.h"

namespace Engine {

class Engine {
public:
    Engine();
    
    void Render();
    void Update();
    void Shutdown();

    bool GetEngineShouldTerminate() const;
private:
    std::unique_ptr<Renderer> m_renderer;

    int m_Initialize();

    Graphics::Quad m_quads[2];

    bool m_engineShouldTerminate = false;

    GLuint m_shaderProgram = 0;
    GLFWwindow* m_window = nullptr;
};

} // namespace Engine

#endif //ENGINE_H
