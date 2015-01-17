#include <common.h>
#include "io.h"
#include "logger.h"

#include "scriptengine.h"

int main(int argc, char **argv) {
    //if(argc < 2) return 0;

    //string fileName = argv[1];

    ScriptEngine *engine = ScriptEngine::create();
    engine->run(IO::readFile("scripts/test.es" /*fileName*/));

    delete engine;

#if DEBUG
    Logger::flush();
#endif

    return 0;
}
