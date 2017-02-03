#include "expression/ast/selfexpression.h"

#include "esther.h"
#include "runtime/context.h"

namespace es {

Ptr<Object> SelfExpression::exec(Esther *esther) {
    return esther->context()->getSelf();
}
}
