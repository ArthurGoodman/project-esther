#pragma once

#include "valueobject.h"

class Integer : public ValueObject {
public:
    Integer(int value);
    Integer();

    void setValue(int value);

    bool equals(IObject *other);
    std::string toString();
};
