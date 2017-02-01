#pragma once

#include "Rootclass.h"

class BooleanClass : public RootClass {
public:
    BooleanClass(Esther *esther);

    void setupMethods(Esther *esther) override;

protected:
    Pointer<Object> createNewInstance(Esther *esther, const std::vector<Pointer<Object>> &args) override;
};
