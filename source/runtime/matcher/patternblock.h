#pragma once

#include <list>

#include "block.h"

class Case;

class PatternBlock : public Block {
    std::list<Case *> cases;

public:
    PatternBlock(std::list<Case *> cases);

    IObject *eval(Context *context);
    IObject *eval(IObject *object, Context *context);
};
