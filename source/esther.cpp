#include "esther.h"

#include "iengine.h"
#include "object.h"
#include "io.h"

Esther Esther::esther;

Esther::Esther() {
    IEngine::initialize();
}

Esther::~Esther() {
    IEngine::release();
}

void Esther::runFile(const string &fileName) {
    Object *value = IEngine::instance()->runFile(fileName);

    if (value)
        IO::printLine("\n=> " + value->toString());
}
