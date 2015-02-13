#pragma once
#include "common.h"

#include "block.h"

namespace esther {

class NativeBlock : public Block {
    function<Object *(Object *, Tuple *)> body;

public:
    NativeBlock(function<Object *(Object *, Tuple *)> body);

    Object *eval(Context *context);

    Object *eval(Object *self, Tuple *args);
};
}
