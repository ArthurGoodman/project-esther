#pragma once
#include "common.h"

class Engine {
public:
    static Engine *create();

    virtual ~Engine();

    virtual void run(const string &script) = 0;

    virtual void initialize() = 0;
    virtual void release() = 0;
};
