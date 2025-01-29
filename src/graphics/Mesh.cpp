//
// Created by linuxmint on 1/27/25.
//

#include "Mesh.h"

namespace Graphics {
    int Mesh::Generate(const float x, const float y, const float width, const float height) {
        // Define vertex data
        const float vertices[] = {
            x, y, 0.0f,
            x + width, y, 0.0f,
            x + width, y + height, 0.0f,
            x, y, 0.0f,
            x + width, y + height, 0.0f,
            x, y + height, 0.0f
        };

        // Create a vertex buffer object (VBO) and vertex array object (VAO)
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);

        // Bind the VAO
        glBindVertexArray(vao);

        // Bind the VBO and copy vertex data
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Set vertex attribute pointers
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void *>(nullptr));
        glEnableVertexAttribArray(0);

        // Unbind the VBO and VAO
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        return 0;
    }

    void Mesh::Render() const {
        // Bind the VAO and draw the triangle
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);

    }

    void Mesh::Clear() const {
        // Clean up
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
    }
} // Engine