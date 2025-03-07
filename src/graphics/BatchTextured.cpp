#include "graphics/BatchTextured.h"

#include "utils/Logger.h"

namespace Graphics {
    BatchTextured::BatchTextured(GLuint texture_id) {
        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);
        glGenBuffers(1, &m_ebo);
        glGenBuffers(1, &m_uvbo);

        m_textureID = texture_id;

        Utils::Logger::Log("BatchTextured Created With Texture ID", m_textureID);
    }

    BatchTextured::~BatchTextured() {
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(1, &m_vbo);
        glDeleteBuffers(1, &m_ebo);
        glDeleteBuffers(1, &m_uvbo);
    }

    void BatchTextured::SubmitMesh(const Mesh& mesh) {
        m_isChanged = true;

        size_t vertex_offset = m_vertices.size();
        m_vertices.insert(m_vertices.end(), mesh.vertices.begin(), mesh.vertices.end());
        m_uvs.insert(m_uvs.end(), mesh.uvs.begin(), mesh.uvs.end());
        m_indices.insert(m_indices.end(), mesh.indices.begin(), mesh.indices.end());

        for (auto& index : mesh.indices) {
            m_indices.push_back(static_cast<unsigned int>(vertex_offset + index));
        }
    }

    void BatchTextured::ApplyMeshChanges() {
        if (!m_isChanged)
            return;

        glBindVertexArray(m_vao);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(glm::vec3), m_vertices.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

        glBindBuffer(GL_ARRAY_BUFFER, m_uvbo);
        glBufferData(GL_ARRAY_BUFFER, m_uvs.size() * sizeof(glm::vec2), m_uvs.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);
        glBindVertexArray(0);

        glActiveTexture(GL_TEXTURE0);

        m_isEmpty = false;
    }

    void BatchTextured::Render() const {
        if (m_isEmpty)
            return;

        glBindVertexArray(m_vao);
        glBindTexture(GL_TEXTURE_2D, m_textureID);
        glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    void BatchTextured::Clear() {
        m_vertices.clear();
        m_uvs.clear();
        m_indices.clear();
    }
}
