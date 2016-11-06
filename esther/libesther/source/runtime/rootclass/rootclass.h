#pragma once

#include <functional>

#include "class.h"

class Runtime;

class RootClass : public Class {
    friend class Runtime;

protected:
    Runtime *runtime;

    RootClass(Runtime *runtime, const std::string &name, Class *superclass);

    virtual void setupMethods() = 0;

    void def(const std::string &name, const std::function<Object *(Object *, const std::vector<Object *> &)> &body);
};
