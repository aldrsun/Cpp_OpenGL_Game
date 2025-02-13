#include "MeshDynamic.h"

#include "../utils/Logger.h"

namespace Graphics {
    MeshDynamic::MeshDynamic(const GLsizei max_quad_count, const GLuint& shader_program) {
        m_shaderProgram = shader_program;
        m_transformLocation = glGetUniformLocation(shader_program, "transform");
        m_maxQuadCount = max_quad_count;

        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);

        glGenBuffers(1, &m_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 4 * max_quad_count, nullptr, GL_DYNAMIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, color));
        
        uint32_t indices[max_quad_count * 6];
        for(int i = 0, v = 0; i < max_quad_count * 6; i += 6, v += 4)
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

    void MeshDynamic::UpdateGeometry(Quad *quads, GLsizei quad_count) {
        m_quadCount = quad_count;
        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        // We can improve this including some control over offset etc.
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Quad) * quad_count, quads);
        glBindVertexArray(0);
    }

    void MeshDynamic::Render() const {
        glBindVertexArray(m_vao);
        glDrawElements(GL_TRIANGLES, m_quadCount * 6, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    }

    void MeshDynamic::Clear() {
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(1, &m_vbo);
        glDeleteBuffers(1, &m_ebo);
    }
} // Graphics