#include "gameobjects/Camera.h"

#include <math.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include "utils/Logger.h"

namespace GameObjects {

    Camera::Camera(const glm::vec3& position, const glm::vec3& target) {
        m_vPosition = position;
        m_vFront = glm::normalize(target - position);
        m_vRight = glm::normalize(glm::cross(m_vFront, m_vUp));
        m_CalculateViewMatrix();
        m_CalculatePerspectiveMatrix();
    }

    glm::vec3 Camera::GetPosition() const {
        return m_vPosition;
    }

    glm::mat4 Camera::GetTransformation() const {
        return m_mTransformation;
    }

    glm::vec3 Camera::GetFront() const {
        return m_vFront;
    }

    glm::vec3 Camera::GetRight() const {
        return m_vRight;
    }

    void Camera::SetPosition(const glm::vec3& position) {
        m_vPosition = position;
        m_CalculateViewMatrix();
    }

    void Camera::LookAt(const glm::vec3& target) {
        if(target == m_vPosition) {
            Utils::Logger::Log(Utils::Logger::LogLevel::Error, "Camera target set same as camera position.");
            return;
        }
        m_vFront = glm::normalize(target - m_vPosition);
        m_vRight = glm::normalize(glm::cross(m_vFront, m_vUp));
        m_CalculateViewMatrix();
    }

    void Camera::SetPitchYaw(const float& pitch, const float& yaw) {
        LookAt(m_vPosition + glm::vec3(
            sinf(yaw) * cosf(pitch),
            sinf(pitch),
            cosf(yaw) * cosf(pitch)));
    }

    void Camera::m_CalculateViewMatrix() {
        glm::vec3 true_up = glm::cross(m_vRight, m_vFront);

        m_mView = glm::mat4(
            glm::vec4(m_vRight, 0.0f),
            glm::vec4(true_up, 0.0f),
            glm::vec4(-m_vFront, 0.0f),
            glm::vec4(m_vPosition, 1.0f)
        );

        m_mView = glm::inverse(m_mView);
        m_mTransformation = m_mPerspective * m_mView;
    }

    void Camera::m_CalculatePerspectiveMatrix() {
        float fov = glm::radians(90.0f);
        float aspectRatio = 1.0f;
        float nearClip = 0.1f;
        float farClip = 100.0f;

        m_mPerspective = glm::perspective(fov, aspectRatio, nearClip, farClip);
        m_mTransformation = m_mPerspective * m_mView;
    }

}
