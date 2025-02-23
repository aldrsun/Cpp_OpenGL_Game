#include "gameobjects/singleobjects/Triangular.h"

namespace GameObjects {

    Triangular::Triangular() {
        m_AssignID();
    }

    void Triangular::m_AssignID() {
        static unsigned int s_triangularCount = 0;
        m_id = s_triangularCount;
        s_triangularCount ++;
    }

    unsigned int Triangular::GetID() const
    {
        return m_id;
    }

    void Triangular::SetMeshID(unsigned int mesh_id) {
        m_meshID = mesh_id;
    }

    unsigned int Triangular::GetMeshID() const {
        return m_meshID;
    }

}