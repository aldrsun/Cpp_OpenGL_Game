#include "Application.h"
#include "../graphics/Shader.h"
#include "../graphics/Mesh.h"
#include "../utils/Logger.h"
#include <cmath>
//#include "../input/InputManager.h" // Upcoming..

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
        std::vector<std::vector<float>> vertices;
        vertices.reserve(6);
        constexpr float delta_angle = (2 * 3.14159265) / 6;
        constexpr float sin_delta_angle = std::sin(delta_angle);
        constexpr float cos_delta_angle = std::cos(delta_angle);
        float x = 1.0f;
        float y = 0.0f;
        for (int i = 0; i < 6; i++) {
            // Simply, (1, 0) * ((cos(d_a), i * sin(d_a)) ^ n)
            // Or (previous_x, previous_y) * (cos(d_a), i * sin(d_a))
            vertices.emplace_back(std::vector<float>{x, y});
            float temp_previous_x = x;
            x = x * cos_delta_angle - y * sin_delta_angle;
            y = temp_previous_x * sin_delta_angle + y * cos_delta_angle;
        }
        m_mesh = std::make_unique<Graphics::Mesh>(vertices);
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
    }

    void Application::m_Render() {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Use the shader program
        glUseProgram(m_shaderProgram);

        m_mesh->Render();

        // Swap buffers and poll events
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

    void Application::m_Shutdown() {
        Utils::Logger::Log("Shutting down application...");
        // Clean up resources

        m_mesh->Clear(); // Temporary for dev purposes

        glDeleteProgram(m_shaderProgram);

        // Terminate GLFW
        glfwTerminate();
        m_applicationShouldTerminate = true;
    }
} // Game