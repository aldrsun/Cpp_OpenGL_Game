#include "engine/Application.h"

#include "engine/Engine.h"
#include <iostream>

namespace Engine {

    void Application::AppRun() {
        while(!m_applicationShouldTerminate)
        {
            Update();
            Render();
            m_applicationShouldTerminate = GetEngineShouldTerminate();
        }
    }
} // namespace Engine