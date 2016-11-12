#include "esther.h"

#include "io.h"
#include "object.h"
#include "exception.h"

void Esther::run(const std::string &script) {
    engine()->run(script);
}

void Esther::runFile(const std::string &fileName) {
    Object *value = engine()->runFile(fileName);

    try {
        if (value)
            IO::writeLine("=> " + value->toString());
    } catch (Exception *e) {
        IO::writeLine(e->message());
        delete e;
    }
}

Engine *Esther::engine() {
    static Engine engine;
    return &engine;
}
