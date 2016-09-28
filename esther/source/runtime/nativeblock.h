#pragma once

#include <functional>
#include <list>

#include "block.h"

class NativeBlock : public Block {
    std::function<Object *(const std::list<Object *> &)> f;

public:
    NativeBlock(const std::function<Object *(const std::list<Object *> &)> &f);

    Object *eval(Context *context);
};
