#include "scriptengine.h"

#include "estherengine.h"

ScriptEngine *ScriptEngine::defaultEngine = 0;

ScriptEngine *ScriptEngine::getDefaultEngine()
{
    return defaultEngine ? defaultEngine : defaultEngine = new Esther::EstherEngine();
}
