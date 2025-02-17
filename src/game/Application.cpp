#include "Application.h"

#include "../engine/core/Engine.h"

namespace Game {
    
void Run() {

    Engine::Engine *engine = new Engine::Engine;
    delete engine;
    engine = NULL;

    return;
}


} // Game