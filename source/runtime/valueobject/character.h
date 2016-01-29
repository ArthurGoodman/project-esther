#pragma once

#include "valueobject.h"

class Character : public ValueObject {
public:
    Character(char value);
    Character();

    void setValue(char value);

    bool equals(IObject *other);
    std::string toString();
};
