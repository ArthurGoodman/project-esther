#pragma once

#include <cstdint>

namespace es {

class ManagedObject {
    uint32_t flags;
    ManagedObject *forwardAddress;
    size_t size;

public:
    enum {
        FlagMark = 1 << 0,
        FlagFree = 1 << 2
    };

    static void *operator new(size_t size) noexcept;
    static void *operator new(size_t size, void *p) noexcept;
    static void operator delete(void *p) noexcept;

    ManagedObject(size_t size = 0);
    virtual ~ManagedObject();

    bool hasFlag(int flag) const;
    void setFlag(int flag);
    void removeFlag(int flag);

    ManagedObject *getForwardAddress() const;
    void setForwardAddress(ManagedObject *forwardAddress);

    size_t getSize() const;

    virtual void finalize();
    virtual void mapOnReferences(void (*f)(ManagedObject *&));

protected:
    void setSize(size_t size);
};

inline bool ManagedObject::hasFlag(int flag) const {
    return flags & flag;
}

inline void ManagedObject::setFlag(int flag) {
    flags |= flag;
}

inline void ManagedObject::removeFlag(int flag) {
    flags &= ~flag;
}

inline ManagedObject *ManagedObject::getForwardAddress() const {
    return forwardAddress;
}

inline void ManagedObject::setForwardAddress(ManagedObject *forwardAddress) {
    this->forwardAddress = forwardAddress;
}

inline size_t ManagedObject::getSize() const {
    return size;
}

inline void ManagedObject::setSize(size_t size) {
    this->size = size;
}
}
