#include "graphics/Shader.h"
#include <fstream>
#include <sstream>
#include "utils/Logger.h"
#include <GLFW/glfw3.h>

namespace Shader {
    std::string ReadShaderFile(const char* file_path) {
        std::ifstream shader_file(file_path);
        if (!shader_file.is_open()) {
            Utils::Logger::Log(Utils::Logger::LogLevel::Error, "Failed to open shader file: ", file_path);
            return "";
        }
        std::stringstream shaderStream;
        shaderStream << shader_file.rdbuf();
        shader_file.close();
        return shaderStream.str();
    }

    GLuint CompileShader(GLenum shader_type, const char* shader_source) {
        GLuint shader = glCreateShader(shader_type);
        glShaderSource(shader, 1, &shader_source, nullptr);
        glCompileShader(shader);

        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            Utils::Logger::Log(Utils::Logger::LogLevel::Error, "Shader compilation failed:\n", infoLog);
            return 0;
        }
        return shader;
    }

    GLuint CreateShaderProgram(const char* vertex_shader_path, const char* fragment_shader_path) {
        std::string vertex_shader_source = Shader::ReadShaderFile(vertex_shader_path);
        std::string fragment_shader_source = Shader::ReadShaderFile(fragment_shader_path);

        GLuint vertex_shader = CompileShader(GL_VERTEX_SHADER, vertex_shader_source.c_str());
        if (vertex_shader == 0) return 0;

        GLuint fragment_shader = CompileShader(GL_FRAGMENT_SHADER, fragment_shader_source.c_str());
        if (fragment_shader == 0) return 0;

        GLuint shader_program = glCreateProgram();
        glAttachShader(shader_program, vertex_shader);
        glAttachShader(shader_program, fragment_shader);
        glLinkProgram(shader_program);

        GLint success;
        glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetProgramInfoLog(shader_program, 512, nullptr, infoLog);
            Utils::Logger::Log("Shader program linking failed:\n", infoLog);
            return 0;
        }

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);

        return shader_program;
    }
} // namespace Shader