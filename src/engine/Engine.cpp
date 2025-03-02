#include "engine/Engine.h"
#include "engine/Initialization.h"

#include "graphics/Shader.h"
#include "graphics/MeshStatic.h"
#include "utils/Logger.h"

namespace Engine {
    Engine::Engine() {
        Utils::Logger::Log("Engine::Engine()");
        m_Initialize();
    }

    int Engine::m_Initialize() {   
        Utils::Logger::Log("Initializing application...");

        if (m_GLFWInit(&m_window) != 0) {
            Utils::Logger::Log("Failed to initialize GLFW");
            return -1;
        } else {
            Utils::Logger::Log("GLFW Initialized");
        }

        if (m_GLEWInit() != 0) {
            Utils::Logger::Log("Failed to initialize GLEW");
            return -1;
        } else {
            Utils::Logger::Log("GLEW Initialized");
        } 

        if(m_ShaderInit(m_shaderColored, "../res/shaders/colored.vert", "../res/shaders/colored.frag") != 0) {
            Utils::Logger::Log("Failed to initialize Colored Mesh Shaders");
        } else {
            Utils::Logger::Log("Colored Mesh Shaders initialized");
        }

        if(m_ShaderInit(m_shaderTextured, "../res/shaders/textured.vert", "../res/shaders/textured.frag") != 0) {
            Utils::Logger::Log("Failed to initialize Textured Mesh Shaders");
        } else {
            Utils::Logger::Log("Textured Mesh Shaders initialized");
        }

        renderer = std::move(std::make_unique<Renderer>(m_window, m_shaderColored, m_shaderTextured));
        return 0;
    }

    void Engine::Shutdown() {
        Utils::Logger::Log("Shutting down application...");

        renderer->Clear();

        glDeleteProgram(m_shaderColored);
        glDeleteProgram(m_shaderTextured);

        glfwTerminate();
    }

    bool Engine::GetEngineShouldTerminate() const {
        return glfwWindowShouldClose(m_window);
    }
} // namespace Engine