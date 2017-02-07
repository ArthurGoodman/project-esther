#pragma once

#include "memory/managedobject.h"

namespace es {

class FreeObject : public ManagedObject {
public:
    FreeObject(size_t size);
};
}
