#pragma once

#include "rootclass.h"

class NullClass : public RootClass {
public:
    NullClass(Esther *esther);

    void setupMethods(Esther *esther);

    void copy(ManagedObject *dst);

protected:
    Pointer<Object> createNewInstance(const std::vector<Pointer<Object>> &args);
};
