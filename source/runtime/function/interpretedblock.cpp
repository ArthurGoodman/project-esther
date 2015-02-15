#include "interpretedblock.h"

#include "expression.h"

InterpretedBlock::InterpretedBlock(Expression *e)
    : e(e) {
}

Object *InterpretedBlock::eval(Context *context) {
    return e->eval(context);
}
