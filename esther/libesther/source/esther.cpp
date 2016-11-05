#include "esther.h"

void Esther::run(const std::string &script) {
    engine()->run(script);
}

void Esther::runFile(const std::string &fileName) {
    engine()->runFile(fileName);
}

Engine *Esther::engine() {
    static Engine engine;
    return &engine;
}
