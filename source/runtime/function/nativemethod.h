#pragma once
#include "common.h"

#include "method.h"

class NativeBlock;

class NativeMethod : public Method {
public:
    NativeMethod(string name, Signature *signature, NativeBlock *body, Object *self, bool isStatic = false);

    Object *execute(Object *self, Tuple *args);
};
