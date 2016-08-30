#pragma once

#include <stack>

#include "source.h"

class Object;
class Context;

class Engine {
    std::stack<Source> sources;
    std::stack<std::string> fileNames;

public:
    Engine();
    ~Engine();

    Object *run(const std::string &script);
    Object *runFile(const std::string &fileName);

private:
    void pushSource(const std::string &source);
    void popSource();

    void pushFileName(const std::string &fileName);
    void popFileName();

    const Source &source();
    const std::string &fileName();
};
