#pragma once
#include "common.h"

#include "engine.h"

class Context;

class DefaultEngine : public Engine {
    stack<string> sources; // This is used in error messages to show the line containing errors.

public:
    Object *run(const string &script);
    Object *run(const string &script, Context *context);

protected:
    void initializeEngine();
    void releaseEngine();

private:
    void pushSource(const string &source);
    void popSource();

    // Current source code access point.
    const string &source();
};
