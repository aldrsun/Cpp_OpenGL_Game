#include "Application.h"
#include "../graphics/Shader.h"
#include "../graphics/MeshStatic.h"
#include "../utils/Logger.h"

namespace Game {
    Application::Application() {
        Utils::Logger::Log("Application::Application()");
        m_Initialize();
    }

    int Application::m_Initialize() {
        Utils::Logger::Log("Initializing application...");
        // Initialize GLFW and GLEW
        if (!glfwInit()) {
            Utils::Logger::Log("Failed to initialize GLFW");
            return -1;
        }

        // Create a windowed mode window and its OpenGL context
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        m_window = glfwCreateWindow(800, 800, "OpenGL Snake Game", nullptr, nullptr);
        if (!m_window) {
            Utils::Logger::Log("Failed to create GLFW window");
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(m_window);

        // Initialize GLEW
        if (glewInit() != GLEW_OK) {
            Utils::Logger::Log("Failed to initialize GLEW");
            return -1;
        }

        // Load shader source code
        std::string vertex_shader_source = Shader::readShaderFile("../res/shaders/default.vert");
        std::string fragment_shader_source = Shader::readShaderFile("../res/shaders/default.frag");

        if (vertex_shader_source.empty() || fragment_shader_source.empty()) {
            return -1;
        }

        // Create the shader program
        m_shaderProgram = Shader::createShaderProgram(vertex_shader_source.c_str(), fragment_shader_source.c_str());
        if (m_shaderProgram == 0) {
            return -1;
        }

        m_GenerateGameObjects(); // Temporary

        return 0;
    }

    int Application::m_GenerateGameObjects() { // Temporary, for dev purposes
        
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

        return 0;
    }

    void Application::Run() {
        while (!m_applicationShouldTerminate) {
            if (!glfwWindowShouldClose(m_window)) {
                m_Update();
                m_Render();
            } else {
                m_applicationShouldTerminate = true;
            }
        }

        m_Shutdown();
    }

    void Application::m_Update() {
        // Handle input and update game state
        static int direction = 1;
        for (int i = 0; i < 4; i ++) {
            m_quads[0].vertices[i].position[0] += 0.01 * direction;
        }
        if(m_quads[0].vertices[0].position[0] < -1 || m_quads[0].vertices[2].position[0] > 1) {
            direction *= -1;
        }

    }

    void Application::m_Render() {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Use the shader program
        glUseProgram(m_shaderProgram);

        m_meshDynamic->UpdateGeometry(m_quads, 2);
        m_meshDynamic->Render();

        // Swap buffers and poll events
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

    void Application::m_Shutdown() {
        Utils::Logger::Log("Shutting down application...");
        // Clean up resources

        m_meshDynamic->Clear();

        glDeleteProgram(m_shaderProgram);

        // Terminate GLFW
        glfwTerminate();
        m_applicationShouldTerminate = true;
    }
} // Game