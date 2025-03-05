#include "engine/Application.h"

#include "engine/Engine.h"

#include "gameobjects/Rectangle.h"

#include <chrono>
#include "utils/Logger.h"

#include "engine/EventManager.h"

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
	    glm::vec3(-0.5f, -0.75f, 0.0f),
	    glm::vec3( 0.0f, -0.75f, 0.0f),
	    glm::vec3( 0.0f, -0.25f, 0.0f),
	    glm::vec3(-0.5f, -0.25f, 0.0f)
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
            glm::vec3(0.25f, 0.80f, 0.0f),
            glm::vec3(0.75f, 0.80f, 0.0f),
            glm::vec3(0.75f, 0.30f, 0.0f),
            glm::vec3(0.25f, 0.30f, 0.0f),
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

      //  renderer->SubmitMesh(texturedMesh);

        while(!m_applicationShouldTerminate)
        {
            glClear(GL_COLOR_BUFFER_BIT);
            renderer->Render();

            glfwSwapBuffers(window);

            glfwPollEvents();
            m_applicationShouldTerminate = GetEngineShouldTerminate();
        }

        Shutdown();
    }
} // namespace Engine
