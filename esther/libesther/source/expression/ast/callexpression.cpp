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

Pointer<Object> CallExpression::exec(Esther *esther) {
    Pointer<Object> evaledF = f->eval(esther);
    Pointer<Object> evaledSelf = self->eval(esther);

    std::vector<Pointer<Object>> evaledArgs;

    for (int i = args - 1; i >= 0; i--)
        evaledArgs << esther->top(i);

    return evaledSelf->call(esther, evaledF, evaledArgs);
}
