#pragma once
#include "common.h"

#include "valueobject.h"

class Character : public ValueObject {
public:
    Character(char value);
    Character();
};
