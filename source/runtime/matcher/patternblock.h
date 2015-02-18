#pragma once
#include "common.h"

#include "block.h"

class Case;

class PatternBlock : public Block {
    list<Case *> cases;

public:
    PatternBlock(list<Case *> cases);

    Object *eval(Context *context);
    Object *eval(Object *object, Context *context);
};
