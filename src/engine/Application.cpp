#include "engine/Application.h"

#include "engine/EventManager.h"

namespace Engine {

    void Application::AppRun() {

        while(!m_applicationShouldTerminate)
        {

            glfwPollEvents();
            EventManager::GetInstance().Dispatch();

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            renderer->Render();

            glfwSwapBuffers(window);

            m_applicationShouldTerminate = GetEngineShouldTerminate();
        }

        Shutdown();
    }
} // namespace Engine
