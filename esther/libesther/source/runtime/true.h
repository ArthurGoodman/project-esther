#pragma once

#include "object.h"

class True : public Object {
    friend class Runtime;

public:
    std::string toString() const;

private:
    True(Class *objectClass);
};
