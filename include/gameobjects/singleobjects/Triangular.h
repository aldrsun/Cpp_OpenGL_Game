#ifndef TRIANGULAR_H
#define TRIANGULAR_H

#include <vector>
#include <array>
#include <memory>

namespace GameObjects {
    // TODO : WORK ON THESE
    class Triangular {
        public:
            Triangular();

            unsigned int GetID() const;
            unsigned int GetMeshID() const;
            void SetMeshID(unsigned int mesh_id);
        private:
            unsigned int m_id;
            unsigned int m_meshID;
            void m_AssignID();
    };
} // namespace GameObjects

#endif // TRIANGULAR_H