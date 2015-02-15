#pragma once
#include "common.h"

#include "rootclass.h"

class CharacterClass : public RootClass {
public:
    CharacterClass();

    Object *newInstance();

    void setupMethods();
};
