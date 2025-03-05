#include "engine/Engine.h"
#include "engine/Initialization.h"

#include "gameobjects/Camera.h"

#include "graphics/Shader.h"
#include "utils/Logger.h"

namespace Engine {
    Engine::Engine() {
        Utils::Logger::Log("Engine::Engine()");
        m_Initialize();
    }

    int Engine::m_Initialize() {   
        Utils::Logger::Log("Initializing application...");

        if (m_GLFWInit(&window) != 0) {
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
            Utils::Logger::Log("Colored Mesh Shaders initialized", m_shaderColored);
        }

        if(m_ShaderInit(m_shaderTextured, "../res/shaders/textured.vert", "../res/shaders/textured.frag") != 0) {
            Utils::Logger::Log("Failed to initialize Textured Mesh Shaders");
        } else {
            Utils::Logger::Log("Textured Mesh Shaders initialized", m_shaderTextured);
        }

        std::shared_ptr<GameObjects::Camera> camera = std::make_shared<GameObjects::Camera>(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f));

        renderer = std::move(std::make_unique<Renderer>(1 /*TEMP TEXTURE ID, TODO.*/, m_shaderColored, m_shaderTextured, camera));
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
        return glfwWindowShouldClose(window);
    }
} // namespace Engine
