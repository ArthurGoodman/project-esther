#pragma once
#include "common.h"

#include "functionfeature.h"

class Class;

class SelfCheckerFeature : public FunctionFeature {
    Class *selfClass;

public:
    SelfCheckerFeature(Class *selfClass);

    void check(Object *self, Tuple *args);
};
