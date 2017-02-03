#include "stackexpression.h"

#include "runtime/esther.h"

StackExpression::StackExpression(int index)
    : index(index) {
}

Ptr<Object> StackExpression::exec(Esther *esther) {
    return esther->top(index);
}