#pragma once

#include "object.h"

class False : public Object {
    friend class Runtime;

public:
    std::string toString() const;

    bool isTrue() const;

private:
    False(Class *objectClass);
};
