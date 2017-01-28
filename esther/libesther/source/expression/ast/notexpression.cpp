#include "notexpression.h"

#include "context.h"
#include "esther.h"

NotExpression::NotExpression(Expression *self)
    : self(self) {
}

NotExpression::~NotExpression() {
    delete self;
}

Object *NotExpression::exec(Esther *esther) {
    return esther->toBoolean(!self->eval(esther)->isTrue());
}
