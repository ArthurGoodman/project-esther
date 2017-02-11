#pragma once

#include <cstdint>

#include "common/config.h"

#ifdef MEM_MANAGEMENT

namespace es {

class ObjectHeader {
    uint32_t flags;
    size_t size;

#ifndef CONSERVATIVE_GC
    ObjectHeader *forwardAddress;
#endif

public:
    enum {
        FlagMark = 1 << 0,
        FlagFree = 1 << 1
    };

    ObjectHeader(size_t size, uint32_t flags = 0);

    bool hasFlag(int flag) const;
    void setFlag(int flag);
    void removeFlag(int flag);

    size_t getSize() const;
    void setSize(size_t size);

#ifndef CONSERVATIVE_GC
    ObjectHeader *getForwardAddress() const;
    void setForwardAddress(ObjectHeader *forwardAddress);
#endif
};

inline bool ObjectHeader::hasFlag(int flag) const {
    return flags & flag;
}

inline void ObjectHeader::setFlag(int flag) {
    flags |= flag;
}

inline void ObjectHeader::removeFlag(int flag) {
    flags &= ~flag;
}

inline size_t ObjectHeader::getSize() const {
    return size;
}

inline void ObjectHeader::setSize(size_t size) {
    this->size = size;
}

#ifndef CONSERVATIVE_GC
inline ObjectHeader *ObjectHeader::getForwardAddress() const {
    return forwardAddress;
}

inline void ObjectHeader::setForwardAddress(ObjectHeader *forwardAddress) {
    this->forwardAddress = forwardAddress;
}
#endif
}

#endif
