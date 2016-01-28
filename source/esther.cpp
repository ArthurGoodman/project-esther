#include "esther.h"

#include "iengine.h"
#include "object.h"
#include "io.h"
#include "exception.h"

void Esther::runFile(const string &fileName) {
    IObject *value = IEngine::instance()->runFile(fileName);

    // TODO: refactor this
    try {
        if (value)
            IO::printLine("\n=> " + value->callToString());
    } catch (Exception *e) {
        IO::printLine("error: " + e->message());
        delete e;
    }
}
