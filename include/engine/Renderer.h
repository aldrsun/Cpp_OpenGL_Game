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
            Renderer(GLFWwindow* window);

            // FOR NOW WE ARE HANDLING ONLY THE DYNAMIC MESHES. WILL BE IMPROVED
            unsigned int AddMesh(Graphics::MeshType mesh_type, GLsizei max_quad_count, const GLuint& shader_program); // TODO : WILL BE IMPROVED

            void UpdateMesh(unsigned int mesh_id, Graphics::Quad *quads, GLsizei quad_count);

            void Render() const;

            void Clear();
        private:
        GLuint m_shaderProgram;
        std::vector<std::unique_ptr<Graphics::Mesh>> m_meshes;
        GLFWwindow * m_window;
    };

} // namespace Engine

#endif // RENDERER_H