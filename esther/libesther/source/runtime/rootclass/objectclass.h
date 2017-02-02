#pragma once

#include "rootclass.h"

class ObjectClass : public RootClass {
public:
    ObjectClass(Esther *esther);

    void setupMethods(Esther *esther) override;

protected:
    Ptr<Object> createNewInstance(Esther *esther, const std::vector<Ptr<Object>> &args) override;
};
