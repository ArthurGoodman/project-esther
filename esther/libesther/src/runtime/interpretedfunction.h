#pragma once

#include "runtime/function.h"
#include "runtime/context.h"
#include "expression/expression.h"

class InterpretedFunction : public Function {
    std::list<std::string> *params;
    Expression *body;
    Context *context;

public:
    InterpretedFunction(Esther *esther, const std::string &name, const std::list<std::string> &params, Expression *body, Ptr<Context> context);
    ~InterpretedFunction();

    void mapOnReferences(const std::function<void (ManagedObject *&)> &f) override;
    int getSize() const override;

protected:
    Ptr<Object> execute(Esther *esther, Ptr<Object> self, const std::vector<Ptr<Object>> &args) override;
};
