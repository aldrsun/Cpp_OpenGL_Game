#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

namespace GameObjects {

    class Camera {
    public:
        Camera(const glm::vec3& position, const glm::vec3& target);

        glm::mat4 GetTransformation() const;

        glm::vec3 GetPosition() const;
        void SetPosition(const glm::vec3& position);

        void LookAt(const glm::vec3& target);
        void SetPitchYaw(const float& pitch, const float& yaw);

        glm::vec3 GetFront() const;
        glm::vec3 GetRight() const;
    private:
        glm::vec3 m_vUp = glm::vec3(0.0f, 1.0f, 0.0f);

        glm::vec3 m_vPosition;
        glm::vec3 m_vFront;
        glm::vec3 m_vRight;

        glm::mat4 m_mPerspective;
        glm::mat4 m_mView;

        glm::mat4 m_mTransformation;

        void m_CalculateViewMatrix();
        void m_CalculatePerspectiveMatrix();
    };

} // namespace GameObjects


#endif // CAMERA_H
