#pragma once
#include "common.h"

#include "valueobject.h"

class Float : public ValueObject {
public:
    Float(double value);
    Float();
};
