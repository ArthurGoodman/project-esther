#pragma once

#include "rootclass.h"

class ValueObject;

class IntegerClass : public RootClass {
    friend class Esther;

public:
    Pointer<ValueObject> createInteger(int value);

protected:
    Pointer<Object> createNewInstance(const std::vector<Pointer<Object>> &args);

    void setupMethods(Esther *esther);

private:
    IntegerClass(Esther *esther);
};
