#include <common.h>

#include "scriptengine.h"

int main(int argc, char **argv)
{
    if(argc < 2) return 0;

    string fileName = argv[1];

    fileName = "scripts/test.es";

    ScriptEngine *engine = ScriptEngine::getDefaultEngine();
    engine->run(readFile(fileName));

    return 0;
}
