#pragma once
#include "common.h"

#include "iengine.h"
#include "source.h"

class Context;

class Engine : public IEngine {
    stack<Source> sources;
    stack<string> fileNames;

public:
    IObject *run(const string &script, Context *context = 0);
    IObject *runFile(const string &fileName, Context *context = 0);

protected:
    void initializeEngine();
    void releaseEngine();

private:
    void pushSource(const string &source);
    void popSource();

    void pushFileName(const string &fileName);
    void popFileName();

    const Source &source();
    const string &fileName();
};
