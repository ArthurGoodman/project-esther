#pragma once

#include "object.h"

class True : public Object {
    friend class Esther;

public:
    std::string toString() const;

private:
    True(Pointer<Class> objectClass);
};
