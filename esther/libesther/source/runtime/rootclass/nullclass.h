#pragma once

#include "rootclass.h"

class NullClass : public RootClass {
    friend class Esther;

public:
    void copy(ManagedObject *dst);

protected:
    Pointer<Object> createNewInstance(const std::vector<Pointer<Object>> &args);

    void setupMethods(Esther *esther);

private:
    NullClass(Esther *esther);
};
