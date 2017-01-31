#pragma once

#include "rootclass.h"

class ValueObject;

class CharacterClass : public RootClass {
    friend class Esther;

public:
    Pointer<ValueObject> createCharacter(char value);

    void copy(ManagedObject *dst);

protected:
    Pointer<Object> createNewInstance(const std::vector<Pointer<Object>> &args);

    void setupMethods(Esther *esther);

private:
    CharacterClass(Esther *esther);
};
