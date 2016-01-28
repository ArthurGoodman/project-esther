#pragma once
#include "common.h"

#include "block.h"

class Case;

class PatternBlock : public Block {
    list<Case *> cases;

public:
    PatternBlock(list<Case *> cases);

    IObject *eval(Context *context);
    IObject *eval(IObject *object, Context *context);
};
