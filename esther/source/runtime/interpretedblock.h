#pragma once

#include "block.h"
#include "expression.h"

class InterpretedBlock : public Block {
    Expression *e;

public:
    InterpretedBlock(Expression *e);

    Object *eval(Context *context);
};
