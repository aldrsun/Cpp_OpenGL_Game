#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <functional>
#include <unordered_map>
#include <vector>
#include <queue>
#include <memory>

#include "engine/Events.h"

namespace Engine {

    class EventDispatcher {
    public:
        EventDispatcher(const EventDispatcher&) = delete;
        EventDispatcher& operator=(const EventDispatcher&) = delete;
        static EventDispatcher& GetInstance();

        using Callback = std::function<void(const Event&)>;

        void Subscribe(const EventType& event_type, Callback callback);
        void QueueEvent(std::unique_ptr<Event> event, const EventType& event_type);
        void Dispatch();

    private:
        EventDispatcher() = default;

        std::unordered_map<EventType, std::vector<Callback>> m_subscribers;
        std::queue<std::pair<std::unique_ptr<Event>, EventType>> m_eventQueue;
    };



} // namespace Engine

#endif // EVENT_MANAGER_H