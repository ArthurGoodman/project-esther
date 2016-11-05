#pragma once

#include "function.h"
#include "context.h"
#include "expression.h"

class InterpretedFunction : public Function {
    friend class FunctionClass;

    std::list<std::string> params;
    Expression *body;
    Context *context;

public:
    Object *execute(Object *self, const std::list<Object *> &args);

private:
    InterpretedFunction(Class *objectClass, const std::string &name, const std::list<std::string> &params, Expression *body, Context *context);
};
