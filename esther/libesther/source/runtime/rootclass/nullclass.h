#pragma once

#include "rootclass.h"

class NullClass : public RootClass {
public:
    NullClass(Esther *esther);

    void setupMethods(Esther *esther) override;

protected:
    Pointer<Object> createNewInstance(Esther *esther, const std::vector<Pointer<Object>> &args) override;
};
