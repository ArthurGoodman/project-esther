#pragma once

#include "function.h"
#include "context.h"
#include "expression.h"

class InterpretedFunction : public Function {
    std::list<std::string> params;
    Expression *body;
    Context *context;

public:
    InterpretedFunction(const std::string &name, const std::list<std::string> &params, Expression *body);

    void setContext(Context *context);

    Object *execute(Object *self, const std::list<Object *> &args);
};
