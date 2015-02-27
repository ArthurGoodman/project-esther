#pragma once
#include "common.h"

#include "nativemethod.h"

class OverloadedMethod : public NativeMethod {
    list<Method *> methods;

public:
    OverloadedMethod(string name, Object *self, bool staticFlag);

    void addMethod(Method *method);
    list<Method *> getMethods();
};
