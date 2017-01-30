#include "callexpression.h"

#include "context.h"
#include "esther.h"
#include "function.h"

CallExpression::CallExpression(Expression *f, Expression *self, int args)
    : f(f)
    , self(self)
    , args(args) {
}

CallExpression::~CallExpression() {
    delete f;
    delete self;
}

Object *CallExpression::exec(Esther *esther) {
    Object *evaledF = f->eval(esther);
    Object *evaledSelf = self->eval(esther);

    std::vector<Object *> evaledArgs;

    for (int i = args - 1; i >= 0; i--)
        evaledArgs << esther->top(i);

    return evaledSelf->call(esther, evaledF, evaledArgs);
}
