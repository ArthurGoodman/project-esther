#pragma once
#include "common.h"

#include "method.h"

class NativeBlock;

class NativeMethod : public Method {
public:
    NativeMethod(string name, NativeBlock *body);

    Object *invoke(Object *self, Tuple *args);
};
