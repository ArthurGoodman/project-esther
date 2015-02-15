#include "esther.h"

#include "engine.h"
#include "io.h"

Esther Esther::esther;
Engine *Esther::engine;

Esther::Esther() {
    engine = Engine::create();
    engine->initialize();
}

Esther::~Esther() {
    engine->release();
}

void Esther::run(const string &script) {
    engine->run(script);
}

void Esther::runFile(const string &fileName)
{
    engine->run(IO::readFile(fileName));
}
