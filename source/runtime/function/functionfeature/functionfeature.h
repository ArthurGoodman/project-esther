#pragma once
#include "common.h"

class IObject;
class Tuple;

class FunctionFeature {
public:
    virtual void check(IObject *self, Tuple *args) = 0;
};
