#pragma once

#include "runtime/rootclass/rootclass.h"

namespace es {

class ValueObject;

class CharacterClass : public RootClass {
public:
    CharacterClass(Esther *esther);

    void setupMethods(Esther *esther) override;

protected:
    Ptr<Object> createNewInstance(Esther *esther, const std::vector<Ptr<Object>> &args) override;
};
}
