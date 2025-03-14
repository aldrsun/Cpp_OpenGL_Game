#include "engine/Engine.h"
#include "engine/Initialization.h"

#include "gameobjects/Camera.h"

#include "engine/GLFWEvents.h"
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

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        glfwSetCursorPosCallback(window, CursorPositionCallback);
        glfwSetKeyCallback(window, KeyboardCallback);

        if (m_GLEWInit() != 0) {
            Utils::Logger::Log("Failed to initialize GLEW");
            return -1;
        } else {
            Utils::Logger::Log("GLEW Initialized");
        }

        // TODO
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

        if(m_ShaderInit(m_shaderText, "../res/shaders/text.vert", "../res/shaders/text.frag") != 0) {
            Utils::Logger::Log("Failed to initialize Text Shaders");
        } else {
            Utils::Logger::Log("Text Shaders initialized", m_shaderText);
        }


        std::shared_ptr<GameObjects::Camera> camera = std::make_shared<GameObjects::Camera>(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f));

        renderer = std::move(std::make_unique<Renderer>(m_shaderColored, m_shaderTextured, m_shaderText, camera));
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
