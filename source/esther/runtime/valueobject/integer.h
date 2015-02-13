#pragma once
#include "common.h"

#include "valueobject.h"

namespace esther {

class Integer : public ValueObject {
public:
    Integer(int value);
    Integer();
};
}
