#include "Mesh.h"

#include "../utils/Logger.h"

namespace Graphics {
    Mesh::Mesh(const float position[2], const std::vector<std::vector<float>> &vertices_list, const GLuint& shader_program) {
        m_shaderProgram = shader_program;
        m_transformLocation = glGetUniformLocation(shader_program, "transform");
        const size_t vertex_count = vertices_list.size() + 1; // + 1 Vertex in the center of mass

        float sum_x = 0, sum_y = 0;
        for (auto &v : vertices_list) {
            sum_x += v[0];
            sum_y += v[1];
        }

        SetPosition(position[0], position[1]);

        // Define vertex data
        std::vector<float> vertex_data;
        vertex_data.reserve(vertex_count * 2);
        vertex_data.emplace_back(0);
        vertex_data.emplace_back(0);
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

    Mesh::Mesh(const float &x, const float &y, const float &width, const float &height, const GLuint& shader_program) {
        m_shaderProgram = shader_program;
        m_transformLocation = glGetUniformLocation(shader_program, "Transformation");
        SetPosition(x, y);

        // Define vertex data
        std::vector<float> vertex_data;
        vertex_data.reserve(8);
        for (int i = 0; i < 4; i++) { // A trick to make assigning values compact, may be - and probably is unnecessary
            vertex_data.emplace_back(- width / 2.0f + width * static_cast<float>(static_cast<bool>((i + 1) & 2)));
            vertex_data.emplace_back(- height / 2.0f + height * static_cast<float>(static_cast<bool>(i & 2)));
        }

        // Define index data
        std::vector<GLuint> index_data;
        m_indexCount = 6;
        index_data.reserve(m_indexCount);
        for (int i = 0; i < 2; i++) {
            index_data.emplace_back(0);
            index_data.emplace_back(1 + i);
            index_data.emplace_back(2 + i);
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

        // Vertex attribute setup (Position - Location 0)
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), static_cast<void *>(nullptr));
        glEnableVertexAttribArray(0);

        // Vertex attribute setup (Transformation - Location 1)
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), reinterpret_cast<void *>(2 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // Unbind the VAO
        glBindVertexArray(0);
        // Unbind the VBO and EBO
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void Mesh::Render() const {
        // Bind the VAO and draw the mesh
        glUniform2fv(m_transformLocation, 1, m_position);
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

    [[nodiscard]] const float* Mesh::GetPosition() const {
        return &m_position[0];
    }

    void Mesh::SetPosition(const float &x, const float &y) {
        m_position[0] = x;
        m_position[1] = y;
    }
} // Graphics