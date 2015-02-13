#pragma once
#include "common.h"

#include "valueobject.h"

namespace esther {

class Float : public ValueObject {
public:
    Float(double value);
    Float();
};
}
