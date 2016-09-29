#pragma once

#include <functional>
#include <list>

#include "function.h"

class NativeFunction : public Function {
    std::function<Object *(Object *, const std::list<Object *> &)> body;

public:
    NativeFunction(const std::string &name, const std::function<Object *(Object *, const std::list<Object *> &)> &body, int arity);

    Object *execute(Object *self, const std::list<Object *> &args);
};
