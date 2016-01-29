#pragma once

#include "nativeblock.h"

class OverloadedMethod;

class OverloadedMethodBlock : public NativeBlock {
public:
    OverloadedMethodBlock(OverloadedMethod *method);
};
