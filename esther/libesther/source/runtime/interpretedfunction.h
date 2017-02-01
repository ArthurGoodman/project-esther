#pragma once

#include "function.h"
#include "context.h"
#include "expression.h"

class InterpretedFunction : public Function {
    std::list<std::string> *params;
    Expression *body;
    Pointer<Context> context;

public:
    InterpretedFunction(Esther *esther, const std::string &name, const std::list<std::string> &params, Expression *body, Pointer<Context> context);
    ~InterpretedFunction();

    virtual void copy(ManagedObject *dst);
    virtual int getSize() const;

protected:
    Pointer<Object> execute(Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &args);
};
