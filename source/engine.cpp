#include "engine.h"

#include "defaultengine.h"

Engine *Engine::engine;

void Engine::initialize() {
    engine = new DefaultEngine;
    engine->initializeEngine();
}

void Engine::release() {
    engine->releaseEngine();
    delete engine;
}

Engine *Engine::instance() {
    return engine;
}

Engine::~Engine() {
}
