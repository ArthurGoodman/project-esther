#pragma once
#include "common.h"

#include "nativemethod.h"

class OverloadedMethod : public NativeMethod {
    list<Method *> methods;

public:
    OverloadedMethod(string name, IObject *self, bool staticFlag);

    void addMethod(Method *method);
    list<Method *> getMethods();

    void replaceMethod(Method *method);

    IObject *clone();
};
