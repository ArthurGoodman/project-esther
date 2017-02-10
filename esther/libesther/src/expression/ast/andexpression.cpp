#include "expression/ast/andexpression.h"

#include "runtime/object.h"

namespace es {

AndExpression::AndExpression(Expression *self, Expression *arg)
    : self(self)
    , arg(arg) {
}

AndExpression::~AndExpression() {
    delete self;
    delete arg;
}

Object *AndExpression::exec(Esther *esther) {
    Object *volatile self = this->self->eval(esther);

    if (self->isTrue())
        return arg->eval(esther);

    return self;
}
}
