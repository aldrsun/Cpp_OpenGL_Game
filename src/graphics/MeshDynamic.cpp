#include "graphics/MeshDynamic.h"

#include "utils/Logger.h"

namespace Graphics {
    MeshDynamic::MeshDynamic(const GLsizei max_vertex_count) {
        m_maxVertexCount = max_vertex_count;

        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);

        glGenBuffers(1, &m_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 4 * max_vertex_count, nullptr, GL_DYNAMIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, color));
        
        uint32_t indices[max_vertex_count];
        for(int i = 0, v = 0; i < max_vertex_count; i += 6, v += 4)
        {
            indices[i]      = 0 + v;
            indices[i + 1]  = 1 + v;
            indices[i + 2]  = 2 + v;
            indices[i + 3]  = 2 + v;
            indices[i + 4]  = 3 + v;
            indices[i + 5]  = 0 + v;
        }

        glGenBuffers(1, &m_ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void MeshDynamic::UpdateGeometry(Vertex *vertices, GLsizei vertex_count) {
        m_vertexCount = vertex_count;
        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * vertex_count, vertices);
        glBindVertexArray(0);
    }

    void MeshDynamic::Render(GLint transform_location) const {
        glBindVertexArray(m_vao);
        glDrawElements(GL_TRIANGLES, m_vertexCount, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    }

    void MeshDynamic::Clear() {
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(1, &m_vbo);
        glDeleteBuffers(1, &m_ebo);
    }

    [[nodiscard]] const float* MeshDynamic::GetPosition() const {
        return &m_position[0];
    }

    void MeshDynamic::SetPosition(const float x, const float y, const float z) {
        m_position[0] = x;
        m_position[1] = y;
        m_position[2] = z;
    }
} // Graphics