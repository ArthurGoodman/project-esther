#pragma once
#include "common.h"

class Object;
class Tuple;

class FunctionFeature {
public:
    virtual void check(Object *self, Tuple *args) = 0;
};
