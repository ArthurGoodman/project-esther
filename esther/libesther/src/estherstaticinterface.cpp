#include "estherstaticinterface.h"

#include "common/io.h"
#include "runtime/object.h"
#include "exception/exception.h"

void EstherStaticInterface::run(const std::string &script) {
    esther()->run(script);
}

void EstherStaticInterface::runFile(const std::string &fileName) {
    esther()->runFile(fileName);
}

Esther *EstherStaticInterface::esther() {
    static Esther esther;
    return &esther;
}
