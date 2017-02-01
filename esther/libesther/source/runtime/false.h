#pragma once

#include "object.h"

class False : public Object {
public:
    False(Esther *esther);

    std::string toString() const;

    bool isTrue() const;

    void copy(ManagedObject *dst);
};
