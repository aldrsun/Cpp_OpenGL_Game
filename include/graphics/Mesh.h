#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <array>

namespace Graphics {
    
    class Mesh {
    public:
        Mesh() {
            m_AssignID();
        }

        std::vector<glm::vec3> vertices;
        std::vector<glm::vec2> uvs;
        std::vector<glm::vec3> colors;
        std::vector<unsigned int> indices;
        GLuint textureID = 0;

        unsigned int GetID() const { return m_id; }
    private:
        unsigned int m_id;

        void m_AssignID() {
            static unsigned int s_meshCount = 0;
            m_id = s_meshCount;
            s_meshCount ++;
        }
    };

} // namespace Graphics

#endif // MESH_H