
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Engine {

    int m_GLFWInit(GLFWwindow **window);
    int m_GLEWInit();
    int m_ShaderInit(GLuint &shader_program, const char* vertex_shader_source, const char* fragment_shader_source);
    

} // namespace Engine
