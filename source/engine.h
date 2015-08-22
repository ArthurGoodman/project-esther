#pragma once
#include "common.h"

class Object;
class Context;

class Engine {
    static Engine *engine;

public:
    static void initialize();
    static void release();

    static Engine *instance();

    virtual ~Engine();

    virtual Object *run(const string &script) = 0;
    virtual Object *run(const string &script, Context *context) = 0;

protected:
    virtual void initializeEngine() = 0;
    virtual void releaseEngine() = 0;
};
