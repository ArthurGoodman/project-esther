#pragma once

#include "function.h"
#include "context.h"
#include "expression.h"

class InterpretedFunction : public Function {
    friend class FunctionClass;

    std::list<std::string> params;
    Expression *body;
    Context *context;

protected:
    Object *execute(Esther *esther, Object *self, const std::vector<Object *> &args);

private:
    InterpretedFunction(Class *objectClass, const std::string &name, const std::list<std::string> &params, Expression *body, Context *context);
};
