#include "engine.h"

#include "defaultengine.h"

Engine *Engine::create() {
    return new DefaultEngine;
}

Engine::~Engine() {
}
