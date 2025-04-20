#include "engine/Window.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "utils/Logger.h"

namespace Engine {

    Window::Window(unsigned int width, unsigned int height, const char* title) {
        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        m_glfwWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!m_glfwWindow) {
            Utils::Logger::Log("Failed to create GLFW window");
            glfwTerminate();
        } else {
            Utils::Logger::Log("GLFW Window created");
            glfwMakeContextCurrent(m_glfwWindow);
        }

        m_width = width;
        m_height = height;
        m_aspectRatio = static_cast<float>(width) / static_cast<float>(height);
    }

    void Window::SwapBuffers() {
        glfwSwapBuffers(m_glfwWindow);
    }

    float Window::GetWidth() const {
        return m_width;
    }

    float Window::GetHeight() const {
        return m_height;
    }

    float Window::GetAspectRatio() const {
        Utils::Logger::Log("Aspect Ratio:", m_aspectRatio);
        return m_aspectRatio;
    }

    GLFWwindow* Window::GetGLFWWindow() const {
        return m_glfwWindow;
    }
} // namespace Engine
