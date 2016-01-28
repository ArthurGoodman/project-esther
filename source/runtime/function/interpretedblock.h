#pragma once
#include "common.h"

#include "block.h"

class Expression;

class InterpretedBlock : public Block {
    Expression *e;

public:
    InterpretedBlock(Expression *e);

    IObject *eval(Context *context);

    IObject *clone();
};
