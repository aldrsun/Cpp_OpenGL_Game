#include "gameobjects/Rectangle.h"

namespace GameObjects {

    Rectangle::Rectangle() {
        m_AssignID();
    }

    void Rectangle::m_AssignID() {
        static unsigned int s_triangularCount = 0;
        m_id = s_triangularCount;
        s_triangularCount ++;
    }

    unsigned int Rectangle::GetID() const
    {
        return m_id;
    }

    void Rectangle::SetMeshID(unsigned int mesh_id) {
        m_meshID = mesh_id;
    }

    unsigned int Rectangle::GetMeshID() const {
        return m_meshID;
    }

}