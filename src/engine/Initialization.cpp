#include "engine/Initialization.h"
#include "utils/Logger.h"
#include "graphics/Shader.h"

namespace Engine {
    int m_glfwInit(GLFWwindow **window) {
        if (!glfwInit()) {
            Utils::Logger::Log("glfwInit() failed.");
            return -1;
        }
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        *window = glfwCreateWindow(800, 800, "OpenGL Game", nullptr, nullptr);
        if (!*window) {
            Utils::Logger::Log("Failed to create GLFW window");
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(*window);
        return 0;
    }

    int m_glewInit() {
        if (glewInit() != GLEW_OK) {
            return -1;
        }
        return 0;
    }

    int m_shaderInit(GLuint &shader_program) {
        std::string vertex_shader_source = Shader::readShaderFile("../res/shaders/default.vert");
        std::string fragment_shader_source = Shader::readShaderFile("../res/shaders/default.frag");
        if (vertex_shader_source.empty() || fragment_shader_source.empty()) {
            return -1;
        }
        shader_program = Shader::createShaderProgram(vertex_shader_source.c_str(), fragment_shader_source.c_str());
        if (shader_program == 0) {
            return -1;
        }
        return 0;
    }
}