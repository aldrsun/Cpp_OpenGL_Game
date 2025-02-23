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


        m_meshDynamic = std::make_unique<Graphics::MeshDynamic>(2, m_shaderProgram);

        m_quads[0] = {
            {
                {{-0.75f, -0.25f, 0.0f} , {0.8f, 0.14f, 0.14f, 1.0f}},
                {{-0.75f, 0.25f, 0.0f}  , {0.8f, 0.14f, 0.14f, 1.0f}},
                {{-0.25f, 0.25f, 0.0f}  , {0.8f, 0.14f, 0.14f, 1.0f}},
                {{-0.25f, -0.25f, 0.0f} , {0.8f, 0.14f, 0.14f, 1.0f}},
            }
        };
        m_quads[1] = {
            {
                {{0.75f, 0.15f, 0.0f} , {0.78f, 0.32f, 0.0f, 1.0f}},
                {{0.75f, 0.65f, 0.0f}  , {0.78f, 0.32f, 0.0f, 1.0f}},
                {{0.25f, 0.65f, 0.0f}  , {0.78f, 0.32f, 0.0f, 1.0f}},
                {{0.25f, 0.15f, 0.0f} , {0.78f, 0.32f, 0.0f, 1.0f}},
            }
        };

        while (!m_engineShouldTerminate) {
            if (!glfwWindowShouldClose(m_window)) {
                Update();
                Render();
            } else {
                m_engineShouldTerminate = true;
            }
        }

        Shutdown();
        return 0;
    }

    void Engine::Update() {
        static int direction = 1;
        for (int i = 0; i < 4; i ++) {
            m_quads[0].vertices[i].position[0] += 0.01 * direction;
        }
        if(m_quads[0].vertices[0].position[0] < -1 || m_quads[0].vertices[2].position[0] > 1) {
            direction *= -1;
        }

    }

    void Engine::Render() {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(m_shaderProgram);

        m_meshDynamic->UpdateGeometry(m_quads, 2);
        m_meshDynamic->Render();

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

    void Engine::Shutdown() {
        Utils::Logger::Log("Shutting down application...");

        m_meshDynamic->Clear();

        glDeleteProgram(m_shaderProgram);

        glfwTerminate();
    }

    bool Engine::GetEngineShouldTerminate() const {
        return m_engineShouldTerminate;
    }
} // namespace Engine