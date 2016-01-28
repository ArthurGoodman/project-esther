#pragma once
#include "common.h"

#include "functionfeature.h"

class Signature;

class ArgumentsCheckerFeature : public FunctionFeature {
    Signature *signature;

public:
    ArgumentsCheckerFeature(Signature *signature);

    void check(IObject *self, Tuple *args);
};
