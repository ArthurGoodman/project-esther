#pragma once
#include "common.h"

#include "valueobject.h"

class Character : public ValueObject {
public:
    Character(char value);
    Character();

    void setValue(char value);

    bool immediateEquals(Object *other);
    string immediateToString();
};
