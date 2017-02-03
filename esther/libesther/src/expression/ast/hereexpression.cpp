#include "expression/ast/hereexpression.h"

#include "esther.h"
#include "runtime/context.h"

namespace es {

Ptr<Object> HereExpression::exec(Esther *esther) {
    return esther->context()->getHere();
}
}
