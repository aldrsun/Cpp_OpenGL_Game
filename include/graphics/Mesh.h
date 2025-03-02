#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>

#include <vector>
#include <array>

namespace Graphics {

    struct VertexColored {
        float position[3];
        float color[4];
    };

    struct VertexTextured {
        float position[3];
        float textureCoord[2];
    };

    enum class MeshType {
        MESH_DYNAMIC,
        MESH_STATIC,
        MESH_STATIC_TEXTURED
    };

    class Mesh {
    public:
        Mesh();
    // TODO : DO NOT CREATE MESHES IN THEIR CONSTRUCTORS
        virtual void Render(GLint transform_location) const = 0;
        virtual void Clear() = 0;
        virtual void UpdateGeometry(VertexColored* vertices, GLsizei vertex_count) {};
        virtual void UpdateGeometry(VertexTextured* vertices, GLsizei vertex_count, GLuint texture_id) {};
        [[nodiscard]] virtual const float* GetPosition() const = 0;
        virtual void SetPosition(const float x, const float y, const float z) = 0;

        virtual void UpdateGeometry(const std::array<float, 3>& position, const std::vector<VertexColored> &vertex_list) {}
        virtual void UpdateGeometry(const std::array<float, 3>& position, const std::vector<VertexTextured> &vertex_list, GLuint texture_id) {}

        unsigned int GetID() const;
    private:
        unsigned int m_id;
        void m_AssignID();
    };

}

#endif // MESH_H