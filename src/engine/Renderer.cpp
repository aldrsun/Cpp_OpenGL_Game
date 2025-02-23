#include "engine/Renderer.h"

namespace Engine {

    Renderer::Renderer(GLFWwindow* window)
    {
        m_window = window;
    }

    unsigned int Renderer::AddMesh(Graphics::MeshType mesh_type, GLsizei max_quad_count, const GLuint& shader_program)
    {
        m_shaderProgram = shader_program;
        switch (mesh_type)
        {
            case Graphics::MeshType::MESH_DYNAMIC:
                std::unique_ptr<Graphics::Mesh> new_mesh_dynamic = std::make_unique<Graphics::MeshDynamic>(max_quad_count, shader_program);
                unsigned int new_mesh_id = new_mesh_dynamic->GetID();
                m_meshes.push_back(std::move(new_mesh_dynamic));
                return new_mesh_id;
        }

        return 0;
    }

    void Renderer::UpdateMesh(const unsigned int mesh_id, Graphics::Quad *quads, GLsizei quad_count )
    {
        for (const auto& mesh : m_meshes)
        {
            if (mesh->GetID() == mesh_id)
            {

                mesh->UpdateGeometry(quads, quad_count);

                break;
            }
        }
    }

    void Renderer::Render() const {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(m_shaderProgram);

        for (const auto& mesh : m_meshes)
        {
            mesh->Render();
        }
        glfwSwapBuffers(m_window);
    }

    void Renderer::Clear() {
        for (const auto& mesh : m_meshes)
        {
            mesh->Clear();
        }

        m_meshes.clear();
    }

} // namespace Engine