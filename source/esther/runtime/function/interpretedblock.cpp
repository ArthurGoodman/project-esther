#include "interpretedblock.h"

#include "expression.h"

namespace esther {

InterpretedBlock::InterpretedBlock(Expression *e)
    : e(e) {
}

Object *InterpretedBlock::eval(Context *context) {
    return e->eval(context);
}
}
