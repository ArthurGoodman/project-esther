#pragma once

#include "rootclass.h"

class ValueObject;

class FloatClass : public RootClass {
    friend class Esther;

public:
    Pointer<ValueObject> createFloat(double value);

protected:
    Pointer<Object> createNewInstance(const std::vector<Pointer<Object>> &args);

    void setupMethods(Esther *esther);

private:
    FloatClass(Esther *esther);
};
