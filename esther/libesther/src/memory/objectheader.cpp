#include "memory/objectheader.h"

#ifdef MEM_MANAGEMENT

namespace es {

ObjectHeader::ObjectHeader(size_t size, uint32_t flags)
    : flags(flags)
    , size(size)
#ifndef CONSERVATIVE_GC
    , forwardAddress(nullptr)
#endif
{
}
}

#endif
