
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "engine/Window.h"

namespace Engine {

    int m_WindowInit(Window **window, int window_width, int window_height, const char* title);
    int m_GLEWInit();
    int m_ShaderInit(GLuint &shader_program, const char* vertex_shader_source, const char* fragment_shader_source);

} // namespace Engine
