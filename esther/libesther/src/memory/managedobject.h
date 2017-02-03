#pragma once

#include <cstdint>

namespace es {

class ManagedObject {
    uint32_t flags;
    ManagedObject *forwardAddress;

public:
    enum {
        FlagMark = 1 << 0
    };

    static void *operator new(size_t size) noexcept;
    static void *operator new(size_t size, void *p) noexcept;
    static void operator delete(void *p) noexcept;

    ManagedObject();
    virtual ~ManagedObject();

    bool hasFlag(int flag) const;
    void setFlag(int flag);
    void removeFlag(int flag);

    ManagedObject *getForwardAddress() const;
    void setForwardAddress(ManagedObject *forwardAddress);

    virtual void finalize();
    virtual void mapOnReferences(void (*f)(ManagedObject *&));
    virtual int getSize() const = 0;
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
}
