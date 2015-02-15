#pragma once
#include "common.h"

#include "class.h"

class CharacterClass : public Class {
public:
    CharacterClass();

    Object *newInstance();

    void setupMethods();
};
