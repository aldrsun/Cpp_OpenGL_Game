#ifndef MESH_STATIC_H
#define MESH_STATIC_H
#include <GL/glew.h>
#include <vector>
#include <array>

#include "graphics/Mesh.h"

namespace Graphics {

class MeshStatic : public Mesh{
public:
    void UpdateGeometry(const std::array<float, 3>& position, const std::vector<Vertex>& vertex_list) override;
    //MeshStatic(const float& x, const float& y, const float& width, const float& height);
    void Render(GLint transform_location) const override;
    void Clear() override;
    [[nodiscard]] const float* GetPosition() const override;
    void SetPosition(const float x, const float y, const float z) override;
private:
    GLuint m_vao = 0, m_vbo = 0, m_ebo = 0;
    GLsizei m_indexCount;
    float m_position[3] = {0.0f, 0.0f, 0.0f};
};

} // Graphics

#endif //MESH_STATIC_H
