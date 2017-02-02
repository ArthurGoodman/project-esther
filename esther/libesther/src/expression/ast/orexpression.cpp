#include "orexpression.h"

OrExpression::OrExpression(Expression *self, Expression *arg)
    : self(self)
    , arg(arg) {
}

OrExpression::~OrExpression() {
    delete self;
    delete arg;
}

Ptr<Object> OrExpression::exec(Esther *esther) {
    Ptr<Object> self = this->self->eval(esther);

    if (self->isTrue())
        return self;

    return arg->eval(esther);
}
