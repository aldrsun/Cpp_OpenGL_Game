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

    void Shutdown();

    bool GetEngineShouldTerminate() const;

    std::unique_ptr<Renderer> renderer;

    GLFWwindow* window = nullptr;
private:
    int m_Initialize();

    GLuint m_shaderColored = 0;
    GLuint m_shaderTextured = 0;
};

} // namespace Engine

#endif //ENGINE_H
