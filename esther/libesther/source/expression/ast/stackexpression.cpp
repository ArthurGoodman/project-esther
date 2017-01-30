#include "stackexpression.h"

#include "esther.h"

StackExpression::StackExpression(int index)
    : index(index) {
}

Pointer<Object> StackExpression::exec(Esther *esther) {
    return esther->top(index);
}
