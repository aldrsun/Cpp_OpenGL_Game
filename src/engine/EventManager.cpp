#include "engine/EventManager.h"

namespace Engine {
    void EventDispatcher::Subscribe(const EventType& event_type, Callback callback) {
        m_subscribers[event_type].push_back(std::move(callback));
    }

    void EventDispatcher::QueueEvent(std::unique_ptr<Event> event, const EventType& event_type) {
        m_eventQueue.emplace(std::move(event), event_type);
    }

    void EventDispatcher::Dispatch() {
        while (!m_eventQueue.empty()) {
            auto [event, event_type] = std::move(m_eventQueue.front());
            m_eventQueue.pop();

            if (m_subscribers.count(event_type)) {
                for (auto& subscriber : m_subscribers[event_type]) {
                    // maybe static_cast here, instead of the inside of the callback.
                    subscriber(*event);
                }
            }
        }
    }

    EventDispatcher& EventDispatcher::GetInstance() {
        static EventDispatcher s_Instance;
        return s_Instance;
    }

} // namespace Engine
