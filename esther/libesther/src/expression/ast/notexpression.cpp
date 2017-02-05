#include "expression/ast/notexpression.h"

#include "runtime/object.h"
#include "runtime/context.h"
#include "esther.h"

namespace es {

NotExpression::NotExpression(Expression *self)
    : self(self) {
}

NotExpression::~NotExpression() {
    delete self;
}

Object *NotExpression::exec(Esther *esther) {
    return esther->toBoolean(!self->eval(esther)->isTrue());
}
}
