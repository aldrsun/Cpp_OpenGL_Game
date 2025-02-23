#include "engine/Engine.h"

namespace Engine {
class Application : private Engine {
    public:
        void AppRun(); // Temporary
    private:
        bool m_applicationShouldTerminate = false;
};

} // namespace Engine