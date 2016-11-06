#pragma once

#include <functional>

#include "function.h"

class NativeFunction : public Function {
    friend class FunctionClass;

    std::function<Object *(Object *, const std::vector<Object *> &)> body;

protected:
    Object *execute(Object *self, const std::vector<Object *> &args);

private:
    NativeFunction(Class *objectClass, const std::string &name, int arity, const std::function<Object *(Object *, const std::vector<Object *> &)> &body);
};
