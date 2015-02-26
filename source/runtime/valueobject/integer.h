#pragma once
#include "common.h"

#include "valueobject.h"

class Integer : public ValueObject {
public:
    Integer(int value);
    Integer();

    void setValue(int value);
};
