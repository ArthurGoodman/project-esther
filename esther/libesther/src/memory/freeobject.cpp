#include "freeobject.h"

namespace es {

FreeObject::FreeObject(size_t size)
    : ManagedObject(size) {
    setFlag(FlagFree);
}
}
