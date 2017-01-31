#pragma once

#include "Rootclass.h"

class BooleanClass : public RootClass {
    friend class Esther;

public:
    void copy(ManagedObject *dst);

protected:
    Pointer<Object> createNewInstance(const std::vector<Pointer<Object>> &args);

    void setupMethods(Esther *esther);

private:
    BooleanClass(Esther *esther);
};
