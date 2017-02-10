#pragma once

#include "runtime/function.h"
#include "runtime/context.h"
#include "expression/expression.h"

namespace es {

class InterpretedFunction : public Function {
    std::list<std::string> params;
    Expression *body;
    Context *context;

public:
    InterpretedFunction(Esther *esther, const std::string &name, const std::list<std::string> &params, Expression *body, Context *volatile context);

    void finalize() override;
    void mapOnReferences(void (*f)(ManagedObject *&)) override;

protected:
    Object *execute(Esther *esther, Object *volatile self, const std::vector<Object *> &args) override;
};
}
