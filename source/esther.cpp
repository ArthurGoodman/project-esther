#include "esther.h"

#include "engine.h"
#include "object.h"
#include "io.h"

Esther Esther::esther;

Esther::Esther() {
    Engine::initialize();
}

Esther::~Esther() {
    Engine::release();
}

void Esther::runFile(const string &fileName) {
    Object *value = Engine::instance()->runFile(fileName);

    if (value)
        IO::printLine("\n=> " + value->toString());
}
