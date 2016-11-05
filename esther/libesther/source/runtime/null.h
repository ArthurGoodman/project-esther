#pragma once

#include "object.h"

class Null : public Object {
    friend class NullClass;

public:
    std::string toString() const;
    bool isTrue() const;

private:
    Null(Class *objectClass);
};
