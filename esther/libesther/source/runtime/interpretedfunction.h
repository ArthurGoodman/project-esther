#pragma once

#include "function.h"
#include "context.h"
#include "expression.h"

class InterpretedFunction : public Function {
    friend class FunctionClass;

    std::list<std::string> params;
    Expression *body;
    Pointer<Context> context;

public:
    virtual int getSize() const;

protected:
    Pointer<Object> execute(Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &args);

private:
    InterpretedFunction(Pointer<Class> objectClass, const std::string &name, const std::list<std::string> &params, Expression *body, Pointer<Context> context);
};
