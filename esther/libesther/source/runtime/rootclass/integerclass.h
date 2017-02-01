#pragma once

#include "rootclass.h"

class ValueObject;

class IntegerClass : public RootClass {
public:
    IntegerClass(Esther *esther);

    void setupMethods(Esther *esther) override;

protected:
    Pointer<Object> createNewInstance(Esther *esther, const std::vector<Pointer<Object>> &args) override;
};
