#include "engine/Initialization.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "utils/Logger.h"
#include "graphics/Shader.h"

namespace Engine {

    int m_WindowInit(Window **window, int window_width, int window_height, const char* title) {

        if (!glfwInit()) {
            Utils::Logger::Log("glfwInit() failed.");
            return -1;
        }

        /*
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        *window = glfwCreateWindow(window_width, window_height, title, nullptr, nullptr);
        if (!*window) {
            Utils::Logger::Log("Failed to create GLFW window");
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(*window);
        */
        *window = new Window(window_width, window_height, title);
        return 0;
    }

    int m_GLEWInit() {
        if (glewInit() != GLEW_OK) {
            return -1;
        }
        return 0;
    }

    int m_ShaderInit(GLuint &shader_program, const char* vertex_shader_path, const char* fragment_shader_path) {
        shader_program = Shader::CreateShaderProgram(vertex_shader_path, fragment_shader_path);
        if (shader_program == 0) {
            return -1;
        }
        return 0;
    }

}
