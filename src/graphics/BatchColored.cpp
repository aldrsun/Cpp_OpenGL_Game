#include "graphics/BatchColored.h"

namespace Graphics {

    BatchColored::BatchColored() {
        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);
        glGenBuffers(1, &m_colorbo);
        glGenBuffers(1, &m_ebo);
    }

    BatchColored::~BatchColored() {
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(1, &m_vbo);
        glDeleteBuffers(1, &m_colorbo);
        glDeleteBuffers(1, &m_ebo);
        }

    void BatchColored::SubmitMesh(const Mesh& mesh) {
        m_isChanged = true;

        size_t vertex_offset = m_vertices.size();
        m_vertices.insert(m_vertices.end(), mesh.vertices.begin(), mesh.vertices.end());
        m_colors.insert(m_colors.end(), mesh.colors.begin(), mesh.colors.end());
        m_indices.insert(m_indices.end(), mesh.indices.begin(), mesh.indices.end());

        for (auto& index : mesh.indices) {
            m_indices.push_back(static_cast<unsigned int>(vertex_offset + index));
        }
    }

    void BatchColored::ApplyMeshChanges() {
        if (!m_isChanged)
            return;

        glBindVertexArray(m_vao);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(glm::vec3), m_vertices.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

        glBindBuffer(GL_ARRAY_BUFFER, m_colorbo);
        glBufferData(GL_ARRAY_BUFFER, m_colors.size() * sizeof(glm::vec3), m_colors.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);

        glBindVertexArray(0);
        m_isEmpty = false;
    }

    void BatchColored::Render() const {
        if (!m_isEmpty) {
            glBindVertexArray(m_vao);

            glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
        }
    }

    void BatchColored::Clear() {
        m_vertices.clear();
        m_colors.clear();
        m_indices.clear();
    }

} // namespace Graphics
