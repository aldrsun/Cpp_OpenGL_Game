#ifndef BATCH_TEXTURED_H
#define BATCH_TEXTURED_H

#include <GL/glew.h>
#include "graphics/Batch.h"

namespace Graphics {

    class BatchTextured : public Batch {
    public:
        BatchTextured(GLuint texture_id, GLuint shader_program);
    
        ~BatchTextured();
    
        void SubmitMesh(const Mesh& mesh) override;
        void ApplyMeshChanges() override;
    
        void Render() const override;
    
        void Clear() override;
    
    private:
        GLuint m_vao, m_vbo, m_ebo, m_uvbo;
        GLuint m_shaderProgram;
        GLuint m_textureID;
        bool m_isEmpty = true;
        bool m_isChanged = false;

        std::vector<glm::vec3> m_vertices;
        std::vector<glm::vec2> m_uvs;
        std::vector<unsigned int> m_indices;
    };

}

#endif // BATCH_TEXTURED_H
