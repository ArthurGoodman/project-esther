#include "expression/ast/stackexpression.h"

#include "esther.h"

namespace es {

StackExpression::StackExpression(int index)
    : index(index) {
}

Object *StackExpression::exec(Esther *esther) {
    return esther->top(index);
}
}
