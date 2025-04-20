#ifndef EVENTS_H
#define EVENTS_H

namespace Engine {

enum class EventType {
    WindowResize,
    Keyboard,
    MouseMovement,
    CursorTypeChange,
    CollisionEvent // Development Purposes, temporary
};

class Event {
public:
    virtual ~Event() = default;
};

class WindowResizeEvent : public Event {
public:
    int width, height;
    WindowResizeEvent(int w, int h) : width(w), height(h) {}
};

class KeyboardEvent : public Event {
public:
    int key, scancode, action, mods;
    KeyboardEvent( int key, int scancode, int action, int mods) : key(key), scancode(scancode), action(action), mods(mods) {}
};

class MouseMovementEvent : public Event {
public:
    double x, y;
    MouseMovementEvent(double x_movement, double y_movement) : x(x_movement), y(y_movement) {}
};

enum class CursorType {
    HIDDEN,
    VISIBLE
};

class CursorTypeChangeEvent : public Event {
public:
    CursorType type;
    CursorTypeChangeEvent(CursorType cursor_type) : type(cursor_type) {}
};

class CollisionEvent : public Event {
public:
    int count;
    CollisionEvent(int count) : count(count) {}
};

} // namespace Engine

#endif // EVENTS_H
