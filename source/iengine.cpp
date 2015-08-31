#include "iengine.h"

#include "engine.h"

IEngine *IEngine::engine;

void IEngine::initialize() {
    engine = new Engine;
    engine->initializeEngine();
}

void IEngine::release() {
    engine->releaseEngine();
    delete engine;
}

IEngine *IEngine::instance() {
    return engine;
}

IEngine::~IEngine() {
}
