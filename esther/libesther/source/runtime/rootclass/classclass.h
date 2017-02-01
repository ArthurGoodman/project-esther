#pragma once

#include "rootclass.h"

class ClassClass : public RootClass {
public:
    ClassClass(Esther *esther);

    void setupMethods(Esther *esther) override;

protected:
    Pointer<Object> createNewInstance(Esther *esther, const std::vector<Pointer<Object>> &args) override;
};
