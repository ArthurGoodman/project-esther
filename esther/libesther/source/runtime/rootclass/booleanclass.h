#pragma once

#include "Rootclass.h"

class BooleanClass : public RootClass {
public:
    BooleanClass(Esther *esther);

    void setupMethods(Esther *esther);

    void copy(ManagedObject *dst);

protected:
    Pointer<Object> createNewInstance(const std::vector<Pointer<Object>> &args);
};
