#include "andexpression.h"

AndExpression::AndExpression(Expression *self, Expression *arg)
    : self(self)
    , arg(arg) {
}

AndExpression::~AndExpression() {
    delete self;
    delete arg;
}

Pointer<Object> AndExpression::exec(Esther *esther) {
    Pointer<Object> self = this->self->eval(esther);

    if (self->isTrue())
        return arg->eval(esther);

    return self;
}
