#include "engine/Renderer.h"

namespace Engine {

    Renderer::Renderer(GLFWwindow* window, const GLuint shader_program)
    {
        m_window = window;
        m_shaderProgram = shader_program;


        m_transformLocation = glGetUniformLocation(m_shaderProgram, "Transformation");
    }

    unsigned int Renderer::AddMesh(Graphics::MeshType mesh_type)
    {
        switch (mesh_type)
        {
            case Graphics::MeshType::MESH_STATIC:
                std::unique_ptr<Graphics::Mesh> new_mesh_static = std::make_unique<Graphics::MeshStatic>();
                unsigned int new_mesh_id = new_mesh_static->GetID();
                m_meshes.push_back(std::move(new_mesh_static));



                return new_mesh_id;
        }

        return 0;
    }

    void Renderer::UpdateMesh(const unsigned int mesh_id, const std::array<float, 3> position, const std::vector<Graphics::Vertex>& vertex_list)
    {
        for (const auto& mesh : m_meshes)
        {
            if (mesh->GetID() == mesh_id)
            {
                mesh->UpdateGeometry(position, vertex_list);
                break;
            }
        }
    }
    
    void Renderer::UpdateMeshPosition(const unsigned int mesh_id, std::array<float, 3> position)
    {
        for (const auto& mesh : m_meshes)
        {
            if (mesh->GetID() == mesh_id)
            {

                mesh->SetPosition(position[0], position[1], position[2]);

                break;
            }
        }
    }

    void Renderer::Render() const {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(m_shaderProgram);

        for (const auto& mesh : m_meshes)
        {
            mesh->Render(m_transformLocation);
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