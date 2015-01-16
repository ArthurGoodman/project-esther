#include <common.h>

#include "scriptengine.h"

int main(int argc, char **argv) {
    //if(argc < 2) return 0;

    //string fileName = argv[1];

    ScriptEngine *engine = ScriptEngine::create();
    engine->run(readFile("scripts/test.es" /*fileName*/));

    delete engine;

    return 0;
}
