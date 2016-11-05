#pragma once

#include <functional>
#include <list>

#include "function.h"

class NativeFunction : public Function {
    friend class FunctionClass;

    std::function<Object *(Object *, const std::list<Object *> &)> body;

public:
    Object *execute(Object *self, const std::list<Object *> &args);

private:
    NativeFunction(Class *objectClass, const std::string &name, int arity, const std::function<Object *(Object *, const std::list<Object *> &)> &body);
};
