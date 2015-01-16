#pragma once
#include <common.h>

class ScriptEngine {
public:
    static ScriptEngine *create();

    virtual ~ScriptEngine();
    virtual void run(const string &script) = 0;
};
