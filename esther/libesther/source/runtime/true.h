#pragma once

#include "object.h"

class True : public Object {
public:
    True(Esther *esther);

    std::string toString() const;

    void copy(ManagedObject *dst);
};
