#include "engine/Application.h"

#include "engine/Engine.h"

#include "gameobjects/Rectangle.h"

#include <chrono>
#include "utils/Logger.h"

#include "engine/EventManager.h"

namespace Engine {

    void Application::AppRun() {

        GameObjects::Rectangle quad1, quad2;

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
        
        auto start_time = std::chrono::high_resolution_clock::now(); // Start time
        int frame_count = 0;

        int collision_count = 0;

        EventDispatcher::GetInstance().Subscribe(EventType::CollisionEvent, [](const Event& event) {
            const CollisionEvent& collision_event = static_cast<const CollisionEvent&>(event);
            Utils::Logger::Log("Collision! : ", collision_event.count);
        });

        while(!m_applicationShouldTerminate)
        {        
            auto current_time = std::chrono::high_resolution_clock::now();  // Current time
            std::chrono::duration<float> elapsed = current_time - start_time;  // Time elapsed in seconds
            frame_count ++;

            EventDispatcher::GetInstance().Dispatch();



            if (x_pos < -0.75 || x_pos > 0.75) {
                EventDispatcher::GetInstance().QueueEvent(std::make_unique<CollisionEvent>(collision_count ++), EventType::CollisionEvent);
            }

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

            if (elapsed.count() >= 1.0f) {
                float fps = frame_count / elapsed.count();
                Utils::Logger::Log("FPS: ", fps);
    
                // Reset for next second
                frame_count = 0;
                start_time = std::chrono::high_resolution_clock::now();
            }
    
        }

        Shutdown();
    }
} // namespace Engine
