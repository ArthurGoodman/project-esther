#include "expression/ast/popexpression.h"

#include "esther.h"

namespace es {

PopExpression::PopExpression(int count)
    : count(count) {
}

Object *PopExpression::exec(Esther *esther) {
    esther->pop(count);
    return esther->getReg();
}
}
