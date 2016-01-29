#pragma once

#include "nativemethod.h"

class OverloadedMethod : public NativeMethod {
    std::list<Method *> methods;

public:
    OverloadedMethod(const std::string &name, IObject *self, bool staticFlag);

    void addMethod(Method *method);
    std::list<Method *> getMethods();

    void replaceMethod(Method *method);

    IObject *clone();
};
