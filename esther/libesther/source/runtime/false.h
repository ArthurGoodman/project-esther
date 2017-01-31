#pragma once

#include "object.h"

class False : public Object {
    friend class Esther;

public:
    std::string toString() const;

    bool isTrue() const;

    void copy(ManagedObject *dst);

private:
    False(Pointer<Class> objectClass);
};
