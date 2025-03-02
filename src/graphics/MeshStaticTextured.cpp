#include "graphics/MeshStaticTextured.h"

#include "utils/Logger.h"

namespace Graphics {
    void MeshStaticTextured::UpdateGeometry(const std::array<float, 3>& position, const std::vector<VertexTextured>& vertex_list, GLuint texture_id){
        m_textureID = texture_id;
        SetPosition(position[0], position[1], position[2]);

        if (m_vao != 0)
        {
            glDeleteVertexArrays(1, &m_vao);
            glDeleteBuffers(1, &m_vbo);
            glDeleteBuffers(1, &m_ebo);
        }

        uint32_t indices[6];
        for(int i = 0, v = 0; i < vertex_list.size(); i += 6, v += 4)
        {
            indices[i]      = 0 + v;
            indices[i + 1]  = 1 + v;
            indices[i + 2]  = 2 + v;
            indices[i + 3]  = 2 + v;
            indices[i + 4]  = 3 + v;
            indices[i + 5]  = 0 + v;
        }
        m_indexCount = 6;
        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);
        glGenBuffers(1, &m_ebo);
        glBindVertexArray(m_vao);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(VertexTextured) * vertex_list.size()), &vertex_list[0], GL_STATIC_DRAW);
        
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexTextured), (const void*)offsetof(VertexTextured, position));

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexTextured), (const void*)offsetof(VertexTextured, textureCoord));

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void MeshStaticTextured::Render(GLint transform_location) const {
        glUniform3f(transform_location, m_position[0], m_position[1], m_position[2]);
        glBindVertexArray(m_vao);
        glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    }

    void MeshStaticTextured::Clear() {
        glDeleteVertexArrays(1, &m_vao);
        m_vao = 0;
        glDeleteBuffers(1, &m_vbo);
        m_vbo = 0;
        glDeleteBuffers(1, &m_ebo);
        m_ebo = 0;
    }

    [[nodiscard]] const float* MeshStaticTextured::GetPosition() const {
        return &m_position[0];
    }

    void MeshStaticTextured::SetPosition(const float x, const float y, const float z) {
        m_position[0] = x;
        m_position[1] = y;
        m_position[2] = z;
    }
} // Graphics