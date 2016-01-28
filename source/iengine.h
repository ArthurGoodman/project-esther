#pragma once
#include "common.h"

class IObject;
class Context;

class IEngine {
    static IEngine *engine;

public:
    static void initialize();
    static void release();

    static IEngine *instance();

    virtual ~IEngine();

    virtual IObject *run(const string &script, Context *context = 0) = 0;
    virtual IObject *runFile(const string &fileName, Context *context = 0) = 0;

protected:
    virtual void initializeEngine() = 0;
    virtual void releaseEngine() = 0;
};
