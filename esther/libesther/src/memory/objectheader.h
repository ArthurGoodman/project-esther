#pragma once

#include <cstdint>

namespace es {

class ObjectHeader {
    uint32_t flags;
    ObjectHeader *forwardAddress;
    size_t size;

public:
    enum {
        FlagMark = 1 << 0,
        FlagFree = 1 << 2
    };

    ObjectHeader(size_t size);

    bool hasFlag(int flag) const;
    void setFlag(int flag);
    void removeFlag(int flag);

    ObjectHeader *getForwardAddress() const;
    void setForwardAddress(ObjectHeader *forwardAddress);

    size_t getSize() const;
    void setSize(size_t size);
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

inline ObjectHeader *ObjectHeader::getForwardAddress() const {
    return forwardAddress;
}

inline void ObjectHeader::setForwardAddress(ObjectHeader *forwardAddress) {
    this->forwardAddress = forwardAddress;
}

inline size_t ObjectHeader::getSize() const {
    return size;
}

inline void ObjectHeader::setSize(size_t size) {
    this->size = size;
}
}
