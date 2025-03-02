#include "engine/Renderer.h"

#include "utils/Logger.h"

namespace Engine {

    Renderer::Renderer(GLFWwindow* window, const GLuint shader_colored, const GLuint shader_textured)
    {
        m_window = window;
        m_shaderColored = shader_colored;
        m_shaderTextured = shader_textured;


        m_transformLocationColored = glGetUniformLocation(m_shaderColored, "Transformation");
        m_transformLocationTextured = glGetUniformLocation(m_shaderTextured, "Transformation");
    }

    unsigned int Renderer::AddMesh(Graphics::MeshType mesh_type)
    {
        switch (mesh_type)
        {
            case Graphics::MeshType::MESH_STATIC:
            {
                std::unique_ptr<Graphics::Mesh> new_mesh_static_colored = std::make_unique<Graphics::MeshStatic>();
                unsigned int new_mesh_id = new_mesh_static_colored->GetID();
                m_meshesColored.push_back(std::move(new_mesh_static_colored));
                Utils::Logger::Log("Created Mesh Static Colored: ", new_mesh_id);
                return new_mesh_id;
            }
            
            case Graphics::MeshType::MESH_STATIC_TEXTURED:
            {
                std::unique_ptr<Graphics::Mesh> new_mesh_static_textured = std::make_unique<Graphics::MeshStaticTextured>();
                unsigned int new_mesh_id = new_mesh_static_textured->GetID();
                m_meshesTextured.push_back(std::move(new_mesh_static_textured));
                Utils::Logger::Log("Created Mesh Static Textured: ", new_mesh_id);
                return new_mesh_id;
            }
        }

        return 0;
    }

    void Renderer::UpdateMesh(const unsigned int mesh_id, const std::array<float, 3> position, const std::vector<Graphics::VertexColored>& vertex_list)
    {
        for (const auto& mesh_colored : m_meshesColored)
        {
            if (mesh_colored->GetID() == mesh_id)
            {
                mesh_colored->UpdateGeometry(position, vertex_list);
                break;
            }
        }
    }
    
    void Renderer::UpdateMesh(const unsigned int mesh_id, const std::array<float, 3> position, const std::vector<Graphics::VertexTextured>& vertex_list, GLuint texture_id)
    {
        for (const auto& mesh_textured : m_meshesTextured)
        {
            if (mesh_textured->GetID() == mesh_id)
            {
                mesh_textured->UpdateGeometry(position, vertex_list, texture_id);
                break;
            }
        }
    }
    
    void Renderer::UpdateMeshPosition(const unsigned int mesh_id, std::array<float, 3> position)
    {
        for (const auto& mesh : m_meshesColored)
        {
            if (mesh->GetID() == mesh_id)
            {

                mesh->SetPosition(position[0], position[1], position[2]);
                return;
            }
        }

        for (const auto& mesh_textured : m_meshesTextured)
        {
            if (mesh_textured->GetID() == mesh_id)
            {

                mesh_textured->SetPosition(position[0], position[1], position[2]);
                return;
            }
        }
    }

    void Renderer::Render() const {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(m_shaderColored);

        for (const auto& mesh_colored : m_meshesColored)
        {
            mesh_colored->Render(m_transformLocationColored);
        }

        glUseProgram(m_shaderTextured);

        for (const auto& mesh_textured : m_meshesTextured)
        {
            mesh_textured->Render(m_transformLocationTextured);
        }
        glfwSwapBuffers(m_window);
    }

    void Renderer::Clear() {
        for (const auto& mesh_colored : m_meshesColored)
        {
            mesh_colored->Clear();
        }
        for (const auto& mesh_textured : m_meshesTextured)
        {
            mesh_textured->Clear();
        }

        m_meshesColored.clear();
        m_meshesTextured.clear();
    }

} // namespace Engine