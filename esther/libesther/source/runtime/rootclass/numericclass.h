#pragma once

#include "rootclass.h"

class NumericClass : public RootClass {
    friend class Esther;

protected:
    void setupMethods();

private:
    NumericClass(Esther *e);
};
