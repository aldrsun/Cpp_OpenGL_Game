#include "graphics/Mesh.h"

namespace Graphics {

    Mesh::Mesh() {
        m_AssignID();
    }

    void Mesh::m_AssignID() {
        static unsigned int s_meshCount = 0;
        m_id = s_meshCount;
        s_meshCount ++;
    }

    unsigned int Mesh::GetID() const {
        return m_id;
    }

}