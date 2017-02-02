#pragma once

#include "runtime/object.h"

class False : public Object {
public:
    False(Esther *esther);

    std::string toString() const override;

    bool isTrue() const override;
};
