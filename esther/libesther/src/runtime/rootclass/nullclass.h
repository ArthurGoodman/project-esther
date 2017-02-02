#pragma once

#include "runtime/rootclass/rootclass.h"

class NullClass : public RootClass {
public:
    NullClass(Esther *esther);

    void setupMethods(Esther *esther) override;

protected:
    Ptr<Object> createNewInstance(Esther *esther, const std::vector<Ptr<Object>> &args) override;
};
