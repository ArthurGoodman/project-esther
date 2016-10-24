#pragma once

#include "valueobject.h"

class String : public ValueObject {
public:
    String(const std::string &value);
    String(const char *value);
    String();

    void setValue(const std::string &value);

    std::string toString();
};
