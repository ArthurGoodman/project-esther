#pragma once

#include "object.h"

class Null : public Object {
public:
    Null(Esther *esther);

    std::string toString() const;
    bool isTrue() const;

    void copy(ManagedObject *dst);
};
