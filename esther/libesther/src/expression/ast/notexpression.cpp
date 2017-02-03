#include "notexpression.h"

#include "runtime/object.h"
#include "runtime/context.h"
#include "runtime/esther.h"

NotExpression::NotExpression(Expression *self)
    : self(self) {
}

NotExpression::~NotExpression() {
    delete self;
}

Ptr<Object> NotExpression::exec(Esther *esther) {
    return esther->toBoolean(!self->eval(esther)->isTrue());
}
