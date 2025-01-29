#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>

namespace Shader {
    std::string readShaderFile(const char* filePath);
    GLuint compileShader(GLenum shaderType, const char* shaderSource);
    GLuint createShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource);
} // namespace Shader


#endif