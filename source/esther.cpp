#include "esther.h"

#include "engine.h"
#include "io.h"

Esther Esther::esther;
esther::Engine *Esther::engine;

Esther::Esther() {
    engine = esther::Engine::create();
    engine->initialize();
}

Esther::~Esther() {
    engine->release();

    IO::closeAllFiles();
}

void Esther::run(const string &script) {
    engine->run(script);
}
