#pragma once
#include "common.h"

#include "functionfeature.h"

class Class;
class Method;

class SelfCheckerFeature : public FunctionFeature {
    Class *selfClass;
    Method *method;

public:
    SelfCheckerFeature(Class *selfClass, Method *method);

    void check(IObject *self, Tuple *args);
};
