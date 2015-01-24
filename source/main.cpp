#include <common.h>
#include "io.h"
#include "logger.h"

#include "scriptengine.h"

int main(int argc, char **argv) {
//    if(argc < 2) return 0;

    string fileName = argc < 2 ? "scripts/test.es" : argv[1];

    ScriptEngine *engine = ScriptEngine::create();
    engine->run(IO::readFile(fileName));

    delete engine;

#if DEBUG
    Logger::flush();
#endif

    return 0;
}
