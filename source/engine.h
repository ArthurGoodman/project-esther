#pragma once
#include "common.h"

#include "iengine.h"
#include "source.h"

class Context;

class Engine : public IEngine {
    // This is used in error messages to show the line containing errors.
    stack<Source> sources;
    stack<string> fileNames;

public:
    Object *run(const string &script, Context *context = 0);
    Object *runFile(const string &fileName, Context *context = 0);

protected:
    void initializeEngine();
    void releaseEngine();

private:
    void pushSource(const string &source);
    void popSource();

    void pushFileName(const string &fileName);
    void popFileName();

    // Current source code access point.
    const Source &source();
    const string &fileName();
};
