#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>

namespace Shader {
    std::string ReadShaderFile(const char* file_path);
    GLuint CompileShader(GLenum shader_type, const char* shader_source);
    GLuint CreateShaderProgram(const char* vertex_shader_source, const char* fragment_shader_source);
} // namespace Shader


#endif