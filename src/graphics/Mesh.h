#ifndef MESH_H
#define MESH_H
#include <GL/glew.h>
#include <vector>

namespace Graphics {

class Mesh {
public:
    explicit Mesh(const std::vector<std::vector<float>>& vertices_list);
    Mesh(const float& x, const float& y, const float& width, const float& height);
    void Render() const;
    void Clear();
private:
    GLuint m_vao = 0, m_vbo = 0, m_ebo = 0;
    GLsizei m_indexCount;
};

} // Engine

#endif //MESH_H
