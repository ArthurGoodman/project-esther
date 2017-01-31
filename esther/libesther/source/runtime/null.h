#pragma once

#include "object.h"

class Null : public Object {
    friend class Esther;

public:
    std::string toString() const;
    bool isTrue() const;

    void copy(ManagedObject *dst);

private:
    Null(Pointer<Class> objectClass);
};
