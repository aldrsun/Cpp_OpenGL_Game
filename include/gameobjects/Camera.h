#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

namespace GameObjects {

    class Camera {
    public:
        Camera(const glm::vec3& position, const glm::vec3& look);

        glm::mat4 GetTransformation() const;

        glm::vec3 GetPosition() const;
        void SetPosition(const glm::vec3& position);
    private:
        glm::vec3 m_vPosition;
        glm::vec3 m_vFront;
        glm::vec3 m_vRight;

        glm::mat4 m_mProjection;
        glm::mat4 m_mTransformation;

        void m_CalculateTransformation();
    };

} // namespace GameObjects


#endif // CAMERA_H