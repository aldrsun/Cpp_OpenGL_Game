#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Application.h"
#include "../graphics/Shader.h"
#include "../graphics/Mesh.h"
#include "../utils/Logger.h"

//#include "../input/InputManager.h"

namespace Game {
    Application::Application() {
        Utils::Logger::Log("Application::Application()");
        Initialize();
    }

    int Application::Initialize() {
        Utils::Logger::Log("Initializing application...");
        // Initialize GLFW, GLEW, etc.
        if (!glfwInit()) {
            Utils::Logger::Log("Failed to initialize GLFW");
            return -1;
        }

        // Create a windowed mode window and its OpenGL context
        GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Shader Program", nullptr, nullptr);
        if (!window) {
            Utils::Logger::Log("Failed to create GLFW window");
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);

        // Initialize GLEW
        if (glewInit() != GLEW_OK) {
            Utils::Logger::Log("Failed to initialize GLEW");
            return -1;
        }

        // Load shader source code
        std::string vertexShaderSource = Shader::readShaderFile("../res/shaders/default.vert");
        std::string fragmentShaderSource = Shader::readShaderFile("../res/shaders/default.frag");

        if (vertexShaderSource.empty() || fragmentShaderSource.empty()) {
            return -1;
        }

        // Create the shader program
        GLuint shaderProgram = Shader::createShaderProgram(vertexShaderSource.c_str(), fragmentShaderSource.c_str());
        if (shaderProgram == 0) {
            return -1;
        }

        GenerateGameObjects();

        // Main loop
        while (!glfwWindowShouldClose(window)) {
            // Clear the screen
            glClear(GL_COLOR_BUFFER_BIT);

            // Use the shader program
            glUseProgram(shaderProgram);

            mesh.Render();

            // Swap buffers and poll events
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        mesh.Clear();

        glDeleteProgram(shaderProgram);

        // Terminate GLFW
        glfwTerminate();
        application_should_terminate = true;
        return 0;
    }

    int Application::GenerateGameObjects() {
        mesh.Generate(-0.5, -0.5, 0.25, 0.75);
        return 0;
    }

    void Application::Run() {
        Update();
        Render();

        if (application_should_terminate) {
            Shutdown();
        }
    }

    void Application::Update() {
        Utils::Logger::Log("Updating application...");
        // Handle input and update game state
    }

    void Application::Render() {
        Utils::Logger::Log("Rendering application...");
        // Render the game
    }

    void Application::Shutdown() {
        Utils::Logger::Log("Shutting down application...");
        // Clean up resources
    }
}