#pragma once

#include "rootclass.h"

class ValueObject;

class CharacterClass : public RootClass {
    friend class Esther;

public:
    ValueObject *createCharacter(char value);

protected:
    Object *createNewInstance(const std::vector<Object *> &args);

    void setupMethods(Esther *esther);

private:
    CharacterClass(Esther *esther);
};
