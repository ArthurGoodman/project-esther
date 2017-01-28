#include "orexpression.h"

OrExpression::OrExpression(Expression *self, Expression *arg)
    : self(self)
    , arg(arg) {
}

OrExpression::~OrExpression() {
    delete self;
    delete arg;
}

Object *OrExpression::exec(Esther *esther) {
    Object *self = this->self->eval(esther);

    if (self->isTrue())
        return self;

    return arg->eval(esther);
}
