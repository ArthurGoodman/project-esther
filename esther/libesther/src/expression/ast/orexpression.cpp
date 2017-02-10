#include "expression/ast/orexpression.h"

#include "runtime/object.h"

namespace es {

OrExpression::OrExpression(Expression *self, Expression *arg)
    : self(self)
    , arg(arg) {
}

OrExpression::~OrExpression() {
    delete self;
    delete arg;
}

Object *OrExpression::exec(Esther *esther) {
    Object *volatile self = this->self->eval(esther);

    if (self->isTrue())
        return self;

    return arg->eval(esther);
}
}
