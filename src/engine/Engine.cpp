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

        if (m_glfwInit(&m_window) != 0) {
            Utils::Logger::Log("Failed to initialize GLFW");
            return -1;
        } else {
            Utils::Logger::Log("GLFW Initialized");
        }

        if (m_glewInit() != 0) {
            Utils::Logger::Log("Failed to initialize GLEW");
            return -1;
        } else {
            Utils::Logger::Log("GLEW Initialized");
        } 

        if(m_shaderInit(m_shaderProgram) != 0) {
            Utils::Logger::Log("Failed to initialize shaders");
        } else {
            Utils::Logger::Log("Shaders initialized");
        }

        renderer = std::move(std::make_unique<Renderer>(m_window, m_shaderProgram));
        return 0;
    }

    void Engine::Shutdown() {
        Utils::Logger::Log("Shutting down application...");

        renderer->Clear();

        glDeleteProgram(m_shaderProgram);

        glfwTerminate();
    }

    bool Engine::GetEngineShouldTerminate() const {
        return glfwWindowShouldClose(m_window);
    }
} // namespace Engine