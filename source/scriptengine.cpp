#include "scriptengine.h"

#include "estherengine.h"

ScriptEngine *ScriptEngine::create() {
    return new esther::EstherEngine();
}

ScriptEngine::~ScriptEngine() {
}
