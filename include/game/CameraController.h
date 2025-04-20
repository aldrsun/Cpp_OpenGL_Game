#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include <memory>

// TODO MOVE EVENTS SOMEWHERE ALSE THAN ENGINE, MAYBE /event
#include "engine/Events.h"
#include "gameobjects/Camera.h"

namespace Game {

    class CameraController {
    public:
        CameraController(std::shared_ptr<GameObjects::Camera> camera);

        void MoveForward(const float& distance);
        void MoveRight(const float& distance);
        void Move(const float& forward_distance, const float& right_distance);

        void Update();

        void MouseMovementEvent(const Engine::MouseMovementEvent& mouse_movement_event);
        void KeyboardEvent(const Engine::KeyboardEvent& keyboard_evenet);

        void LookAt(const glm::vec3& target);
        void SetPitchYaw(const float& pitch, const float& yaw);
   private:
        float m_pitch = 0.0f, m_yaw = 0.0f;
        float m_maxPitch = 1.57f;
        float m_movementSpeed = 0.1f;
        float m_forwardMovement = 0.0f, m_backwardMovement = 0.0f, m_rightMovement = 0.0f, m_leftMovement = 0.0f; // 0.0f or 1.0f
        std::shared_ptr<GameObjects::Camera> m_camera;
    };

}


#endif // CAMERA_CONTROLLER_H
