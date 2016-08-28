#pragma once

#include <string>

class Object;

class IEngine {
public:
    static IEngine *instance();

    virtual ~IEngine();

    virtual Object *run(const std::string &script) = 0;
    virtual Object *runFile(const std::string &fileName) = 0;
};
