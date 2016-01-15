#pragma once
#include "common.h"

#include "functionfeature.h"

class Method;

class StaticSelfCheckerFeature : public FunctionFeature {
    Object *self;
    Method *method;

public:
    StaticSelfCheckerFeature(Object *self, Method *method);

    void check(Object *self, Tuple *args);
};
