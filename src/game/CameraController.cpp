#include "game/CameraController.h"

#include <memory>
#include <math.h>
#define _USE_MATH_DEFINES

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "utils/Logger.h"

namespace Game {

    CameraController::CameraController(std::shared_ptr<GameObjects::Camera> camera) {
        m_camera = camera;
    }

    void CameraController::MoveForward(const float& distance) {
        m_camera->SetPosition(m_camera->GetPosition() + distance * m_camera->GetFront());
    }

    void CameraController::MoveRight(const float& distance) {
        m_camera->SetPosition(m_camera->GetPosition() + distance * m_camera->GetRight());
    }

    void CameraController::Move(const float& forward_distance, const float& right_distance) {
        m_camera->SetPosition(m_camera->GetPosition() + forward_distance * m_camera->GetFront() + right_distance * m_camera->GetRight());
    }

    void CameraController::Update() {
        Move(m_movementSpeed * (m_forwardMovement -m_backwardMovement), m_movementSpeed * (m_rightMovement - m_leftMovement));
    }

    void CameraController::LookAt(const glm::vec3& target) {
        m_camera->LookAt(target);
    }

    void CameraController::SetPitchYaw(const float& pitch, const float& yaw) {
        float new_pitch = pitch;
        if (new_pitch < -m_maxPitch) {
            new_pitch = -m_maxPitch;
        }
        if (new_pitch > m_maxPitch) {
            new_pitch = m_maxPitch;
        }
        m_pitch = new_pitch;
        m_yaw = yaw;
        m_camera->SetPitchYaw(new_pitch, yaw);
    }

    void CameraController::MouseMovementEvent(const Engine::MouseMovementEvent& mouse_movement_event) {
        //Utils::Logger::Log("[Mouse]", mouse_movement_event.x, mouse_movement_event.y, "), [PitchYaw] (", m_pitch, m_yaw);
        SetPitchYaw(m_pitch - mouse_movement_event.y * 0.003, m_yaw - mouse_movement_event.x * 0.003);
    }

    void CameraController::KeyboardEvent(const Engine::KeyboardEvent& keyboard_event) {
         //Utils::Logger::Log("[Keyboard]", keyboard_event.key, keyboard_event.scancode, keyboard_event.action, keyboard_event.mods);
        if (keyboard_event.key == GLFW_KEY_W) {
            if(keyboard_event.action == GLFW_RELEASE) {
                m_forwardMovement = 0.0f;
            } else {
                m_forwardMovement = 1.0f;
            }
        }
        if (keyboard_event.key == GLFW_KEY_A) {
            if(keyboard_event.action == GLFW_RELEASE) {
                m_leftMovement = 0.0f;
            } else {
                m_leftMovement = 1.0f;
            }
        }
        if (keyboard_event.key == GLFW_KEY_S) {
            if(keyboard_event.action == GLFW_RELEASE) {
                m_backwardMovement = 0.0f;
            } else {
                m_backwardMovement = 1.0f;
            }
        }
        if (keyboard_event.key == GLFW_KEY_D) {
            if(keyboard_event.action == GLFW_RELEASE) {
                m_rightMovement = 0.0f;
            } else {
                m_rightMovement = 1.0f;
            }
        }
    }
}
