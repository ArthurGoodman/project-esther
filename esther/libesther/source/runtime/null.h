#pragma once

#include "object.h"

class Null : public Object {
public:
    Null(Esther *esther);

    std::string toString() const override;
    bool isTrue() const override;
};
