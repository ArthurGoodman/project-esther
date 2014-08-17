#pragma once
#include <common.h>

class ScriptEngine
{
    static ScriptEngine *defaultEngine;

public:
    static ScriptEngine *getDefaultEngine();

    virtual void run(string script) = 0;
};
