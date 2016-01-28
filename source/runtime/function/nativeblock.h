#pragma once
#include "common.h"

#include "block.h"

class NativeBlock : public Block {
    function<IObject *(IObject *, Tuple *)> body;

public:
    NativeBlock(function<IObject *(IObject *, Tuple *)> body);

    IObject *eval(Context *context);

    IObject *eval(IObject *self, Tuple *args);

    IObject *clone();
};
