#pragma once
#include "common.h"

#include "valueobject.h"

class String : public ValueObject {
public:
    String(string value);
    String(const char *value);
    String();

    void setValue(string value);

    bool equals(Object *other);
    string toString();
};
