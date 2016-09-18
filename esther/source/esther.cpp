#include "esther.h"

Engine Esther::engine;

void Esther::run(const std::string &script) {
    engine.run(script);
}

void Esther::runFile(const std::string &fileName) {
    engine.runFile(fileName);
}
