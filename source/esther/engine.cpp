#include "engine.h"

#include "defaultengine.h"

namespace esther {

Engine *Engine::create() {
    return new DefaultEngine;
}

Engine::~Engine() {
}
}
