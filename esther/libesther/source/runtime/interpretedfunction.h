#pragma once

#include "function.h"
#include "context.h"
#include "expression.h"

class InterpretedFunction : public Function {
    std::list<std::string> *params;
    Expression *body;
    Context *context;

public:
    InterpretedFunction(Esther *esther, const std::string &name, const std::list<std::string> &params, Expression *body, Pointer<Context> context);
    ~InterpretedFunction();

    void mapOnReferences(const std::function<void (ManagedObject *&)> &f) override;
    int getSize() const override;

protected:
    Pointer<Object> execute(Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &args) override;
};
