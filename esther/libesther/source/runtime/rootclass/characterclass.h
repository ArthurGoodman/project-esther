#pragma once

#include "rootclass.h"

class CharacterClass : public RootClass {
public:
    Object *createCharacter(char value);

    void setupMethods();

protected:
    Object *createNewInstance();
};
