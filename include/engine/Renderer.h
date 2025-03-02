#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "graphics/Mesh.h"
#include "graphics/MeshDynamic.h"
#include "graphics/MeshStatic.h"
#include "graphics/MeshStaticTextured.h"

#include <vector>
#include <memory>

namespace Engine {

    class Renderer {
        public:
            Renderer(GLFWwindow* window, const GLuint shader_colored, const GLuint shader_textured);

            // FOR NOW WE ARE HANDLING ONLY THE DYNAMIC MESHES. WILL BE IMPROVED
            unsigned int AddMesh(Graphics::MeshType mesh_type); // TODO : WILL BE IMPROVED

            void UpdateMesh(const unsigned int mesh_id, const std::array<float, 3> position, const std::vector<Graphics::VertexColored>& vertex_list);
            void UpdateMesh(const unsigned int mesh_id, const std::array<float, 3> position, const std::vector<Graphics::VertexTextured>& vertex_list, GLuint texture_id);
            void UpdateMeshPosition(unsigned int mesh_id, std::array<float, 3> position);

            void Render() const;

            void Clear();
        private:
        GLuint m_shaderColored, m_shaderTextured;
        GLint m_transformLocationColored, m_transformLocationTextured;
        std::vector<std::unique_ptr<Graphics::Mesh>> m_meshesColored;
        std::vector<std::unique_ptr<Graphics::Mesh>> m_meshesTextured;
        GLFWwindow * m_window;
    };

} // namespace Engine

#endif // RENDERER_H