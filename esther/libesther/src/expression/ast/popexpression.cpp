#include "popexpression.h"

#include "runtime/esther.h"

PopExpression::PopExpression(int count)
    : count(count) {
}

Ptr<Object> PopExpression::exec(Esther *esther) {
    esther->pop(count);
    return esther->getReg();
}
