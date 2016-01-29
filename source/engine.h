#pragma once

#include <stack>

#include "iengine.h"
#include "source.h"

class Context;

class Engine : public IEngine {
    std::stack<Source> sources;
    std::stack<std::string> fileNames;

public:
    Engine();
    ~Engine();

    IObject *run(const std::string &script, Context *context = 0);
    IObject *runFile(const std::string &fileName, Context *context = 0);

private:
    void pushSource(const std::string &source);
    void popSource();

    void pushFileName(const std::string &fileName);
    void popFileName();

    const Source &source();
    const std::string &fileName();
};
