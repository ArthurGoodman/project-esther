#pragma once

#include "runtime/object.h"

class True : public Object {
public:
    True(Esther *esther);

    std::string toString() const override;
};