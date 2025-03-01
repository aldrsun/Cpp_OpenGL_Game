#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <vector>
#include <array>
#include <memory>

namespace GameObjects {
    // TODO : WORK ON THESE
    class Rectangle {
        public:
            Rectangle();

            unsigned int GetID() const;
            unsigned int GetMeshID() const;
            void SetMeshID(unsigned int mesh_id);
        private:
            unsigned int m_id;
            unsigned int m_meshID;
            void m_AssignID();
    };
} // namespace GameObjects

#endif // RECTANGLE_H