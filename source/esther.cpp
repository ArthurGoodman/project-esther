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

void Esther::run(const string &script) {
    IO::printLine("\n=> " + Engine::instance()->run(script)->toString());
}

void Esther::runFile(const string &fileName) {
    IO::printLine("\n=> " + Engine::instance()->run(IO::readFile(fileName))->toString());
}
