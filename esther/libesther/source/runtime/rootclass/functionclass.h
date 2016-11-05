#pragma once

#include <functional>

#include "rootclass.h"

class Expression;
class Context;

class FunctionClass : public RootClass {
public:
    Object *createNativeFunction(const std::string &name, int arity, const std::function<Object *(Object *, const std::list<Object *> &)> &body);
    Object *createInterpretedFunction(const std::string &name, const std::list<std::string> &params, Expression *body, Context *context);

    void setupMethods();
};
