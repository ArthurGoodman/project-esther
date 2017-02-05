#pragma once

#include "runtime/rootclass/rootclass.h"

namespace es {

class ValueObject;

class FloatClass : public RootClass {
public:
    FloatClass(Esther *esther);

    void setupMethods(Esther *esther) override;

protected:
    Object *createNewInstance(Esther *esther, const std::vector<Object *> &args) override;
};
}
