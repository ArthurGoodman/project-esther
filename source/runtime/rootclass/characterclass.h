#pragma once
#include "common.h"

#include "rootclass.h"

class CharacterClass : public RootClass {
public:
    CharacterClass();

    void setupMethods();

protected:
    IObject *createNewInstance();
};
