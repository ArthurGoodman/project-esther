#pragma once

#include "functionfeature.h"

class Method;

class StaticSelfCheckerFeature : public FunctionFeature {
    IObject *self;
    Method *method;

public:
    StaticSelfCheckerFeature(IObject *self, Method *method);

    void check(IObject *self, Tuple *args);
};
