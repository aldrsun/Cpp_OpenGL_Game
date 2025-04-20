#ifndef ENGINE_H
#define ENGINE_H

#include <memory>

#include "engine/Window.h"
#include "engine/Renderer.h"

namespace Engine {

class Engine {
public:
    Engine();

    void Shutdown();

    bool GetEngineShouldTerminate() const;

    std::unique_ptr<Renderer> renderer;

    Window* window;
private:
    int m_Initialize();

    GLuint m_shaderColored = 0;
    GLuint m_shaderTextured = 0;
    GLuint m_shaderText = 0;
};

} // namespace Engine

#endif //ENGINE_H
