#pragma once
#include <common.h>

class ScriptEngine
{
    static ScriptEngine *defaultEngine;

public:
    virtual ~ScriptEngine();
    virtual void run(const string &script) = 0;

    static ScriptEngine *getDefaultEngine();
};
