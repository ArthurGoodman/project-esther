#pragma once

#include "runtime/rootclass/rootclass.h"

namespace es {

class ValueObject;

class StringClass : public RootClass {
public:
    StringClass(Esther *esther);

    void setupMethods(Esther *esther) override;

protected:
    Object *createNewInstance(Esther *esther, const std::vector<Object *> &args) override;
};
}
