#pragma once

#include <functional>

#include "block.h"

class NativeBlock : public Block {
    std::function<IObject *(IObject *, Tuple *)> body;

public:
    NativeBlock(std::function<IObject *(IObject *, Tuple *)> body);

    IObject *eval(Context *context);

    IObject *eval(IObject *self, Tuple *args);

    IObject *clone();
};
