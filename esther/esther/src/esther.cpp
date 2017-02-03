#include "esther.h"

void Esther::run(const std::string &script) {
    esther()->run(script);
}

void Esther::runFile(const std::string &fileName) {
    esther()->runFile(fileName);
}

es::Esther *Esther::esther() {
    static es::Esther esther;
    return &esther;
}
