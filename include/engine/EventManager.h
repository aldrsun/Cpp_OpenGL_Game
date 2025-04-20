#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <functional>
#include <unordered_map>
#include <vector>
#include <queue>
#include <memory>

#include "engine/Events.h"

namespace Engine {

    class EventManager {
    public:
        EventManager(const EventManager&) = delete;
        EventManager& operator=(const EventManager&) = delete;
        static EventManager& GetInstance();

        // TODO : MAYBE RAW POINTERS INSTEAD OF std::function
        // TODO : COMPARE A DIFFERENT STRUCTURE WITH RAW POINTERS WITH std::function
        // TODO : ALSO I DID NOT LIKE THE COMPLEXITY OF REGISTERING A SUBSCRIBER. MUST BE SIMPLER
        using Callback = std::function<void(const Event&)>;

        void Subscribe(const EventType& event_type, Callback callback);
        void QueueEvent(std::unique_ptr<Event> event, const EventType& event_type);
        void Dispatch();

    private:
        EventManager() = default;

        std::unordered_map<EventType, std::vector<Callback>> m_subscribers;
        std::queue<std::pair<std::unique_ptr<Event>, EventType>> m_eventQueue;
    };



} // namespace Engine

#endif // EVENT_MANAGER_H
