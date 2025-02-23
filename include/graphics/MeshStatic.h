#ifndef MESH_STATIC_H
#define MESH_STATIC_H
#include <GL/glew.h>
#include <vector>

namespace Engine::Graphics {

class MeshStatic {
public:
    explicit MeshStatic(const float position[2], const std::vector<std::vector<float>>& vertices_list, const GLuint& shader_program);
    MeshStatic(const float& x, const float& y, const float& width, const float& height, const GLuint& shader_program);
    void Render() const;
    void Clear();
    [[nodiscard]] const float* GetPosition() const;
    void SetPosition(const float& x, const float& y);
private:
    GLuint m_shaderProgram;   // TEMPORARY
    GLint m_transformLocation; // TEMPORARY
    GLuint m_vao = 0, m_vbo = 0, m_ebo = 0;
    GLsizei m_indexCount;
    float m_position[2] = {0.0f, 0.0f};
};

} // Graphics

#endif //MESH_STATIC_H
