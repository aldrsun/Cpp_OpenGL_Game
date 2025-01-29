#include "Mesh.h"

#include "../utils/Logger.h"

namespace Graphics {
    Mesh::Mesh(const std::vector<std::vector<float>> &vertices_list) {
        const size_t vertex_count = vertices_list.size() + 1; // + 1 Vertex in the center of mass

        float sum_x = 0, sum_y = 0;
        for (auto &v : vertices_list) {
            sum_x += v[0];
            sum_y += v[1];
        }
        float center_x = sum_x / static_cast<float>(vertex_count);
        float center_y = sum_y / static_cast<float>(vertex_count);

        // Define vertex data
        std::vector<float> vertex_data;
        vertex_data.reserve(vertex_count * 2);
        vertex_data.emplace_back(center_x);
        vertex_data.emplace_back(center_y);
        for (auto &v : vertices_list) {
            vertex_data.emplace_back(v[0]);
            vertex_data.emplace_back(v[1]);
        }

        // Define index data
        std::vector<GLuint> index_data;
        m_indexCount = static_cast<GLsizei>(vertex_count * 3 - 3);
        index_data.reserve(m_indexCount);
        for (int i = 0; i < vertex_count - 1; ++i) {
            index_data.emplace_back(0);
            index_data.emplace_back(i + 1);
            if (i + 2 == vertex_count) {
                index_data.emplace_back(1);
            }
            else {
                index_data.emplace_back(i + 2);
            }
        }

        // Create a vertex buffer object (VBO), element array buffer object (EBO) and vertex array object (VAO)
        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);
        glGenBuffers(1, &m_ebo);

        // Bind the VAO
        glBindVertexArray(m_vao);

        // Bind the VBO and copy vertex data
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(float) * vertex_data.size()), &vertex_data[0], GL_STATIC_DRAW);

        // Bind the EBO and copy the index data
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(index_data.size() * sizeof(GLuint)), &index_data[0], GL_STATIC_DRAW);

        // Vertex attribute setup
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), static_cast<void *>(nullptr));
        glEnableVertexAttribArray(0);

        // Unbind the VAO
        glBindVertexArray(0);
        // Unbind the VBO and EBO
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    Mesh::Mesh(const float &x, const float &y, const float &width, const float &height) {
        m_indexCount = 0;
    }


    void Mesh::Render() const {
        // Bind the VAO and draw the mesh
        glBindVertexArray(m_vao);
        glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    }

    void Mesh::Clear() {
        // Clean up
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(1, &m_vbo);
        glDeleteBuffers(1, &m_ebo);
    }
} // Graphics