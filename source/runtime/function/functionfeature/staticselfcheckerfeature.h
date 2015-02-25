#pragma once
#include "common.h"

#include "functionfeature.h"

class StaticSelfCheckerFeature : public FunctionFeature {
    Object *self;

public:
    StaticSelfCheckerFeature(Object *self);

    void check(Object *self, Tuple *args);
};
