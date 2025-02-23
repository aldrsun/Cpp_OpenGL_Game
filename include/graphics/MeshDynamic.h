#ifndef MESH_DYNAMIC_H
#define MESH_DYNAMIC_H
#include <GL/glew.h>
#include <vector>

namespace Engine::Graphics {

struct Vertex {
    float position[3];
    float color[4];
};

struct Quad {
    Vertex vertices[4];
};

class MeshDynamic {
public:
    explicit MeshDynamic(GLsizei max_quad_count, const GLuint& shader_program);
    void UpdateGeometry(Quad *quads, GLsizei quad_count);
    void Render() const;
    void Clear();
private:
    GLuint m_shaderProgram;   // TEMPORARY
    GLint m_transformLocation; // TEMPORARY
    GLuint m_vao = 0, m_vbo = 0, m_ebo;
    GLsizei m_maxQuadCount = 0;
    GLsizei m_quadCount = 0;
};

} // Engine::Graphics

#endif //MESH_DYNAMIC_H
