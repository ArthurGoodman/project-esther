#pragma once

#include <string>

#include "object.h"

class Class : public Object {
    std::string name;

public:
    std::string getName() const;
};
