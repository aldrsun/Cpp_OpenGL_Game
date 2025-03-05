#ifndef BATCH_COLORED_H
#define BATCH_COLORED_H

#include "graphics/Batch.h"

namespace Graphics {
    
    class BatchColored : public Batch {
    public:
        BatchColored();
        ~BatchColored();
    
        void SubmitMesh(const Mesh& mesh) override;

        void ApplyMeshChanges() override;

        void Render() const override;

        void Clear() override;
    
    private:
        GLuint m_vao, m_vbo, m_ebo, m_colorbo;
        bool m_isEmpty = true;
        bool m_isChanged = false;

        std::vector<glm::vec3> m_vertices;
        std::vector<glm::vec3> m_colors;
        std::vector<unsigned int> m_indices;
    };

}

#endif // BATCH_COLORED_H
