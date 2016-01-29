#pragma once

#include "method.h"

class NativeBlock;

class NativeMethod : public Method {
protected:
    NativeMethod(const std::string &className, const std::string &name, Context *context, Signature *signature, NativeBlock *body, IObject *self, bool staticFlag = false);

public:
    NativeMethod(const std::string &name, Signature *signature, NativeBlock *body, IObject *self, bool staticFlag = false);

    IObject *execute(IObject *self, Tuple *args);
};
