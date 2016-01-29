#pragma once

#include "valueobject.h"

class Float : public ValueObject {
public:
    Float(double value);
    Float();

    void setValue(double value);

    bool equals(IObject *other);
    std::string toString();
};
