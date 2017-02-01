#pragma once

#include "rootclass.h"

class ValueObject;

class FloatClass : public RootClass {
public:
    FloatClass(Esther *esther);

    void setupMethods(Esther *esther);

    void copy(ManagedObject *dst);

protected:
    Pointer<Object> createNewInstance(Esther *esther, const std::vector<Pointer<Object>> &args);
};
