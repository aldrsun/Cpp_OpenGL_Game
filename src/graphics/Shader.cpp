#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <GLFW/glfw3.h>

namespace Shader {
    // Function to read a shader file
    std::string readShaderFile(const char* filePath) {
        std::ifstream shaderFile(filePath);
        if (!shaderFile.is_open()) {
            std::cerr << "Failed to open shader file: " << filePath << std::endl;
            return "";
        }
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        return shaderStream.str();
    }

    // Function to compile a shader
    GLuint compileShader(GLenum shaderType, const char* shaderSource) {
        GLuint shader = glCreateShader(shaderType);
        glShaderSource(shader, 1, &shaderSource, nullptr);
        glCompileShader(shader);

        // Check for compilation errors
        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            std::cerr << "Shader compilation failed:\n" << infoLog << std::endl;
            return 0;
        }
        return shader;
    }

    // Function to create a shader program
    GLuint createShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource) {
        // Compile the vertex shader
        GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
        if (vertexShader == 0) return 0;

        // Compile the fragment shader
        GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
        if (fragmentShader == 0) return 0;

        // Link the shaders into a program
        GLuint shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        // Check for linking errors
        GLint success;
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
            std::cerr << "Shader program linking failed:\n" << infoLog << std::endl;
            return 0;
        }

        // Clean up shaders (they are no longer needed after linking)
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return shaderProgram;
    }
} // namespace Graphics