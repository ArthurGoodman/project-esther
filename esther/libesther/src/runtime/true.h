#pragma once

#include "runtime/object.h"

namespace es {

class True : public Object {
public:
    True(Esther *esther);

    std::string toString() const override;
};
}
