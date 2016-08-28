#include "esther.h"

#include "iengine.h"
#include "io.h"

void Esther::runFile(const std::string &fileName) {
    Object *value = IEngine::instance()->runFile(fileName);
}
