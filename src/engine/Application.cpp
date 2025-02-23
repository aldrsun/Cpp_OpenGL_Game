#include "engine/Application.h"

#include "engine/Engine.h"

#include "gameobjects/singleobjects/Triangular.h"

namespace Engine {

    void Application::AppRun() {

        GameObjects::Triangular quad1, quad2;

        std::vector<Graphics::Vertex> quad1_data = {
            {
                {{-0.25f, -0.25f, 0.0f} , {0.8f, 0.14f, 0.14f, 1.0f}},
                {{-0.25f, 0.25f, 0.0f}  , {0.8f, 0.14f, 0.14f, 1.0f}},
                {{0.25f, 0.25f, 0.0f}  , {0.8f, 0.14f, 0.14f, 1.0f}},
                {{0.25f, -0.25f, 0.0f} , {0.8f, 0.14f, 0.14f, 1.0f}},
            }
        };
        std::vector<Graphics::Vertex> quad2_data = {
            {
                {{0.75f, 0.15f, 0.0f} , {0.78f, 0.32f, 0.0f, 1.0f}},
                {{0.75f, 0.65f, 0.0f}  , {0.78f, 0.32f, 0.0f, 1.0f}},
                {{0.25f, 0.65f, 0.0f}  , {0.78f, 0.32f, 0.0f, 1.0f}},
                {{0.25f, 0.15f, 0.0f} , {0.78f, 0.32f, 0.0f, 1.0f}},
            }
        };


        quad1.SetMeshID(renderer->AddMesh(Graphics::MeshType::MESH_STATIC));
        quad2.SetMeshID(renderer->AddMesh(Graphics::MeshType::MESH_STATIC));


        renderer->UpdateMesh(quad1.GetMeshID(), {0.0f, 0.0f, 0.0f}, quad1_data);
        renderer->UpdateMesh(quad2.GetMeshID(), {0.0f, 0.0f, 0.0f}, quad2_data);


        float x_pos = -0.5f;
        float direction = 1;
        float speed = 0.01;

        while(!m_applicationShouldTerminate)
        {
            if (x_pos < -0.75) {
                direction = 1;
            }
            if (x_pos > 0.75) {
                direction = -1;
            }
            x_pos += direction * speed;
            renderer->UpdateMeshPosition(quad1.GetID(), {x_pos, 0.0f, 0.0f});


            renderer->Render();

            glfwPollEvents();
            m_applicationShouldTerminate = GetEngineShouldTerminate();
        }

        Shutdown();
    }
} // namespace Engine