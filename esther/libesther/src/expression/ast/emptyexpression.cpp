#include "expression/ast/emptyexpression.h"

#include "runtime/context.h"
#include "esther.h"

namespace es {

Object *EmptyExpression::exec(Esther *esther) {
    return esther->getNull();
}
}
