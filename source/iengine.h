#pragma once
#include "common.h"

class IObject;
class Context;

class IEngine {
public:
    static IEngine *instance();

    virtual ~IEngine();

    virtual IObject *run(const string &script, Context *context = 0) = 0;
    virtual IObject *runFile(const string &fileName, Context *context = 0) = 0;
};
