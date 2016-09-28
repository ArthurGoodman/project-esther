#include "interpretedblock.h"

InterpretedBlock::InterpretedBlock(Expression *e)
    : e(e) {
}

Object *InterpretedBlock::eval(Context *context) {
    return 0;
}
