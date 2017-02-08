#include "memory/objectheader.h"

namespace es {

ObjectHeader::ObjectHeader(size_t size)
    : flags(0)
    , forwardAddress(nullptr)
    , size(size) {
}
}
