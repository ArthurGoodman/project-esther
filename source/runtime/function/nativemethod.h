#pragma once
#include "common.h"

#include "method.h"

class NativeBlock;

class NativeMethod : public Method {
protected:
    NativeMethod(string className, string name, Context *context, Signature *signature, NativeBlock *body, IObject *self, bool staticFlag = false);

public:
    NativeMethod(string name, Signature *signature, NativeBlock *body, IObject *self, bool staticFlag = false);

    IObject *execute(IObject *self, Tuple *args);
};
