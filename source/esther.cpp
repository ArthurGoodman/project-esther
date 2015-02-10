#include "esther.h"

#include "engine.h"

Esther Esther::esther;
esther::Engine *Esther::engine;

Esther::Esther() {
    engine = esther::Engine::create();
    engine->initialize();
}

Esther::~Esther() {
    engine->release();
}

void Esther::run(const string &script) {
    engine->run(script);
}
