#pragma once

#include "runtime/rootclass/rootclass.h"

namespace es {

class NumericClass : public RootClass {
public:
    NumericClass(Esther *esther);

    void setupMethods(Esther *esther) override;
};
}
