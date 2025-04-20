#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Engine {

    class Window {
    public:
        Window(unsigned int width, unsigned int height, const char* title);

        void SwapBuffers();

        float GetWidth() const;
        float GetHeight() const;
        float GetAspectRatio() const;
        GLFWwindow* GetGLFWWindow() const;
    private:
        GLFWwindow* m_glfwWindow;
        float m_aspectRatio;
        unsigned int m_width, m_height;
    };

} // namespace Engine

#endif // WINDOW_H
