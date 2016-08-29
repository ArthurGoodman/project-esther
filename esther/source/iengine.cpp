#include "iengine.h"
#include "engine.h"

IEngine *IEngine::instance() {
    static Engine engine;
    return &engine;
}

IEngine::~IEngine() {
}
