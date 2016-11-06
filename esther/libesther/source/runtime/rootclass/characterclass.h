#pragma once

#include "rootclass.h"

class ValueObject;

class CharacterClass : public RootClass {
    friend class Runtime;

public:
    ValueObject *createCharacter(char value);

protected:
    Object *createNewInstance();

    void setupMethods();

private:
    CharacterClass(Runtime *runtime, Class *objectClass);
};
