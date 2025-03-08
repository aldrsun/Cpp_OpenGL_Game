#include "engine/Application.h"

#include "engine/Engine.h"

#include "gameobjects/Rectangle.h"

#include <chrono>
#include "utils/Logger.h"

#include "engine/EventManager.h"

// TODO TODO TODO TODO # FOR TEST PURPOSES. PLEASE RESTRUCTURE THIS IMMEDIATELY! # TODO TODO TODO TODO
#include "game/CameraController.h"

namespace Engine {

    void Application::AppRun() {

        Mesh coloredMesh;
        coloredMesh.vertices = {
            glm::vec3(-0.25f, -0.25f, 0.0f),
            glm::vec3(0.25f, -0.25f, 0.0f),
            glm::vec3(0.25f, 0.25f, 0.0f),
            glm::vec3(-0.25f, 0.25f, 0.0f),
        };
        coloredMesh.colors = {
            glm::vec3(0.8f, 0.3f, 0.2f),
            glm::vec3(0.8f, 0.3f, 0.2f),
            glm::vec3(0.8f, 0.3f, 0.2f),
            glm::vec3(0.8f, 0.3f, 0.2f),
        };
        coloredMesh.indices = {
            0, 1, 2, 2, 3, 0
        };

    renderer->SubmitMesh(coloredMesh);

    Mesh texturedMesh;
    texturedMesh.textureID = renderer->AddTexture("../res/textures/texture1.jpg");

    texturedMesh.vertices = {
        glm::vec3(-10.0f, 0.0f, -10.0f),
        glm::vec3(-10.0f, 0.0f,  10.0f),
        glm::vec3( 10.0f, 0.0f,  10.0f),
        glm::vec3( 10.0f, 0.0f, -10.0f)
    };

    texturedMesh.uvs = {
        glm::vec2(0.0f, 0.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(0.0f, 1.0f)
    };

    texturedMesh.indices = {
        0, 1, 2, 2, 3, 0
    };

    renderer->SubmitMesh(texturedMesh);
    renderer->ApplyMeshChanges();

        Mesh coloredMesh2;
        coloredMesh2.vertices = {
            glm::vec3(0.25f, 0.30f, 0.0f),
            glm::vec3(0.75f, 0.30f, 0.0f),
            glm::vec3(0.75f, 0.80f, 0.0f),
            glm::vec3(0.25f, 0.80f, 0.0f),
        };
        coloredMesh2.colors = {
            glm::vec3(0.2f, 0.8f, 0.3f),
            glm::vec3(0.2f, 0.8f, 0.3f),
            glm::vec3(0.2f, 0.8f, 0.3f),
            glm::vec3(0.2f, 0.8f, 0.3f),
        };
        coloredMesh2.indices = {
            0, 1, 2, 2, 3, 0
        };
        renderer->SubmitMesh(coloredMesh2);

        renderer->ApplyMeshChanges();

        Game::CameraController camera_controller(renderer->GetActiveCamera());
        EventManager::GetInstance().Subscribe(EventType::MouseMovement, [&camera_controller](const Event& event) {
                camera_controller.MouseMovementEvent(static_cast<const MouseMovementEvent&>(event));
        });
        EventManager::GetInstance().Subscribe(EventType::Keyboard, [&camera_controller](const Event& event) {
                camera_controller.KeyboardEvent(static_cast<const KeyboardEvent&>(event));
        });
        camera_controller.LookAt(glm::vec3(0.0f, 0.0f, 0.0f));

        //camera_controller.MoveForward(1.0f);
        while(!m_applicationShouldTerminate)
        {

            glfwPollEvents();
            EventManager::GetInstance().Dispatch();
            camera_controller.Update();

            //camera_controller.MoveRight(0.01f);
            //camera_controller.LookAt(glm::vec3(0.0f, 0.0f, 0.0f));

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            renderer->Render();

            glfwSwapBuffers(window);

            m_applicationShouldTerminate = GetEngineShouldTerminate();
        }

        Shutdown();
    }
} // namespace Engine
