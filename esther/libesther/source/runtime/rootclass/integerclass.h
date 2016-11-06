#pragma once

#include "rootclass.h"

class ValueObject;

class IntegerClass : public RootClass {
    friend class Runtime;

public:
    ValueObject *createInteger(int value);

protected:
    Object *createNewInstance();

    void setupMethods();

private:
    IntegerClass(Runtime *runtime);
};
