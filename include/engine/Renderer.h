#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "graphics/Mesh.h"
#include "graphics/MeshDynamic.h"
#include "graphics/MeshStatic.h"

#include <vector>
#include <memory>

namespace Engine {

    class Renderer {
        public:
            Renderer(GLFWwindow* window, const GLuint shader_program);

            // FOR NOW WE ARE HANDLING ONLY THE DYNAMIC MESHES. WILL BE IMPROVED
            unsigned int AddMesh(Graphics::MeshType mesh_type); // TODO : WILL BE IMPROVED

            void UpdateMesh(const unsigned int mesh_id, const std::array<float, 3> position, const std::vector<Graphics::Vertex>& vertex_list);
            void UpdateMeshPosition(unsigned int mesh_id, std::array<float, 3> position);

            void Render() const;

            void Clear();
        private:
        GLuint m_shaderProgram;
        GLint m_transformLocation;
        std::vector<std::unique_ptr<Graphics::Mesh>> m_meshes;
        GLFWwindow * m_window;
    };

} // namespace Engine

#endif // RENDERER_H