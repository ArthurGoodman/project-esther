#pragma once

#include "object.h"

class Null : public Object {
    friend class Esther;

public:
    std::string toString() const;
    bool isTrue() const;

private:
    Null(Pointer<Class> objectClass);
};
