#include "interpretedblock.h"

#include "expression.h"

InterpretedBlock::InterpretedBlock(Expression *e)
    : e(e) {
}

IObject *InterpretedBlock::eval(Context *context) {
    return e->eval(context);
}

IObject *InterpretedBlock::clone() {
    return new InterpretedBlock(e);
}
