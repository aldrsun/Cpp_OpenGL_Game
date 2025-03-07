#include "gameobjects/Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace GameObjects {

    Camera::Camera(const glm::vec3& position, const glm::vec3& look) {
        m_vPosition = position;
        m_vFront = glm::normalize(look - position);
        m_CalculateTransformation();
    }

    glm::mat4 Camera::GetTransformation() const {
        return m_mTransformation;
    }

    glm::vec3 Camera::GetPosition() const {
        return m_vPosition;
    }

    void Camera::SetPosition(const glm::vec3& position) {
        m_vPosition = position;
        m_CalculateTransformation();
    }

    void Camera::m_CalculateTransformation() {
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

        glm::vec3 right = glm::normalize(glm::cross(m_vFront, up));

        glm::vec3 trueUp = glm::cross(right, m_vFront);

        m_mTransformation = glm::mat4(
            glm::vec4(right, 0.0f),
            glm::vec4(trueUp, 0.0f),
            glm::vec4(-m_vFront, 0.0f),
            glm::vec4(m_vPosition, 1.0f)
        );

        m_mTransformation = glm::inverse(m_mTransformation);

        float fov = glm::radians(120.0f);
        float aspectRatio = 1.0f;
        float nearClip = 0.1f;
        float farClip = 100.0f;

        glm::mat4 perspective = glm::perspective(fov, aspectRatio, nearClip, farClip);

        m_mTransformation = perspective * m_mTransformation;
    }

}