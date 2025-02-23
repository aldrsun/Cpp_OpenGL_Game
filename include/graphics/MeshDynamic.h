#ifndef MESH_DYNAMIC_H
#define MESH_DYNAMIC_H

#include <GL/glew.h>
#include "graphics/Mesh.h"

#include <vector>


namespace Graphics {

class MeshDynamic : public Mesh{
public:
    explicit MeshDynamic(GLsizei max_quad_count);
    void UpdateGeometry(Vertex *vertices, GLsizei vertex_count) override;
    void Render(GLint transform_location) const override;
    void Clear() override;

    [[nodiscard]] const float* GetPosition() const override;
    void SetPosition(const float x, const float y, const float z) override;
private:
    GLuint m_vao = 0, m_vbo = 0, m_ebo;
    GLsizei m_maxVertexCount = 0;
    GLsizei m_vertexCount = 0;

    float m_position[2];
};

} // Graphics

#endif //MESH_DYNAMIC_H
