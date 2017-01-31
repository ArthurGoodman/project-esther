#pragma once

#include "rootclass.h"

class NumericClass : public RootClass {
    friend class Esther;

public:
    void copy(ManagedObject *dst);

protected:
    void setupMethods(Esther *esther);

private:
    NumericClass(Esther *esther);
};
