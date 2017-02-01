#pragma once

#include "rootclass.h"

class ObjectClass : public RootClass {
public:
    ObjectClass(Esther *esther);

    void setupMethods(Esther *esther) override;

protected:
    Pointer<Object> createNewInstance(Esther *esther, const std::vector<Pointer<Object>> &args) override;
};
