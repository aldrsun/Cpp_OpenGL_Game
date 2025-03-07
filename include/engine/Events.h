#ifndef EVENTS_H
#define EVENTS_H

namespace Engine {

enum class EventType {
    WindowResize,
    KeyPress,
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

class KeyPressEvent : public Event {
public:
    int keyCode;
    KeyPressEvent(int key_code) : keyCode(key_code) {}
};


class CollisionEvent : public Event {
public:
    int count;
    CollisionEvent(int count) : count(count) {}
};

} // namespace Engine

#endif // EVENTS_H
