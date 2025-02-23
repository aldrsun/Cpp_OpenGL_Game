#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>

namespace Graphics {

    struct Vertex {
        float position[3];
        float color[4];
    };
    
    struct Quad {
        Vertex vertices[4];
    };

    enum class MeshType {
        MESH_DYNAMIC,
        MESH_STATIC
    };

    class Mesh {
    public:
        Mesh();
    // TODO : DO NOT CREATE MESHES IN THEIR CONSTRUCTORS
        virtual void Render() const = 0;
        virtual void Clear() = 0;
        virtual void UpdateGeometry(Quad *quads, GLsizei quad_count) {}; // TODO : TEMPORARY, WILL BE IMPROVED
        [[nodiscard]] virtual const float* GetPosition() const = 0;
        virtual void SetPosition(const float& x, const float& y) = 0;
        
        unsigned int GetID() const;
    private:
        unsigned int m_id;
        void AssignID();
    };

}

#endif // MESH_H