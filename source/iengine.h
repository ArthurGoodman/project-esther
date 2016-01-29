#pragma once

#include <string>

class IObject;
class Context;

class IEngine {
public:
    static IEngine *instance();

    virtual ~IEngine();

    virtual IObject *run(const std::string &script, Context *context = 0) = 0;
    virtual IObject *runFile(const std::string &fileName, Context *context = 0) = 0;
};
