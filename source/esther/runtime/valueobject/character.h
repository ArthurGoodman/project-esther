#pragma once
#include "common.h"

#include "valueobject.h"

namespace esther {

class Character : public ValueObject {
public:
    Character(char value);
    Character();
};
}
