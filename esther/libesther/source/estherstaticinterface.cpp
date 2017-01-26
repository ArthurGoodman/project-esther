#include "estherstaticinterface.h"

#include "io.h"
#include "object.h"
#include "exception.h"

void EstherStaticInterface::run(const std::string &script) {
    esther()->run(script);
}

void EstherStaticInterface::runFile(const std::string &fileName) {
    Object *value = esther()->runFile(fileName);

    try {
        if (value)
            IO::writeLine("=> " + value->toString());
    } catch (Exception *e) {
        IO::writeLine(e->message());
        delete e;
    }
}

Esther *EstherStaticInterface::esther() {
    static Esther esther;
    return &esther;
}
