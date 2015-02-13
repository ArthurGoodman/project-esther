#pragma once
#include "common.h"

#include "class.h"

namespace esther {

class CharacterClass : public Class {
public:
    CharacterClass();

    Object *newInstance();

    void setupMethods();
};
}
