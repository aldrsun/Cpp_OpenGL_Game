#ifndef GLFW_EVENTS_H
#define GLFW_EVENTS_H

#include "engine/Events.h"
#include "engine/EventManager.h"
#include "utils/Logger.h"

namespace Engine {

    static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
        static double previous_x = 0.0;
        static double previous_y = 0.0;
        double x_movement = xpos - previous_x;
        double y_movement = ypos - previous_y;
        previous_x = xpos;
        previous_y = ypos;
        EventManager::GetInstance().QueueEvent(std::make_unique<MouseMovementEvent>(x_movement, y_movement), EventType::MouseMovement);
        }
    static void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        EventManager::GetInstance().QueueEvent(std::make_unique<KeyboardEvent>(key, scancode, action, mods), EventType::Keyboard);
    }

}

#endif // GLFW_EVENTS_H
