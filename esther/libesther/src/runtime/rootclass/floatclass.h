#pragma once

#include "runtime/rootclass/rootclass.h"

class ValueObject;

class FloatClass : public RootClass {
public:
    FloatClass(Esther *esther);

    void setupMethods(Esther *esther) override;

protected:
    Ptr<Object> createNewInstance(Esther *esther, const std::vector<Ptr<Object>> &args) override;
};
