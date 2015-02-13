#pragma once
#include "common.h"

#include "block.h"

namespace esther {

class Expression;

class InterpretedBlock : public Block {
    Expression *e;

public:
    InterpretedBlock(Expression *e);

    Object *eval(Context *context);
};
}
