#pragma once
#include "common.h"

#include "nativeblock.h"

class OverloadedMethod;

class OverloadedMethodBlock : public NativeBlock {
public:
    OverloadedMethodBlock(OverloadedMethod *method);
};
