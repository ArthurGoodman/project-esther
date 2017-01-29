#pragma once

#include "rootclass.h"

class ValueObject;

class IntegerClass : public RootClass {
    friend class Esther;

public:
    ValueObject *createInteger(int value);

protected:
    Object *createNewInstance(const std::vector<Object *> &args);

    void setupMethods(Esther *esther);

private:
    IntegerClass(Esther *esther);
};
