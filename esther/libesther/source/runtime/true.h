#pragma once

#include "object.h"

class True : public Object {
    friend class Esther;

public:
    std::string toString() const;

    void copy(ManagedObject *dst);

private:
    True(Pointer<Class> objectClass);
};
