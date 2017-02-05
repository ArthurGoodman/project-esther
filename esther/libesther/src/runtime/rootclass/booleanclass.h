#pragma once

#include "runtime/rootclass/rootclass.h"

namespace es {

class BooleanClass : public RootClass {
public:
    BooleanClass(Esther *esther);

    void setupMethods(Esther *esther) override;

protected:
    Object *createNewInstance(Esther *esther, const std::vector<Object *> &args) override;
};
}
