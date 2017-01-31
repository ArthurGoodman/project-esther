#pragma once

#include "common/common.h"
#include "memory/frame.h"
#include "memory/pointer.h"

class ManagedObject;

class MemoryManager {
public:
    static MemoryManager *instance();

    template <class T>
    T *allocateArray(uint size);

    virtual ~MemoryManager();

    virtual ManagedObject *allocate(uint size, int count = 1) = 0;
    virtual void free(ManagedObject *p) = 0;

    virtual void collectGarbage() = 0;
    virtual void reallocate() = 0;
};

template <class T>
T *MemoryManager::allocateArray(uint size) {
    return new (instance()->allocate(size * sizeof(T), size)) T[size];
}

#define GC_OPEN_FRAME \
    Frame __gc_frame__([&](std::function<void(ManagedObject *&)> f) {

#define GC_OPEN_STATIC_FRAME \
    static GC_OPEN_FRAME

#define GC_CLOSE_FRAME \
    });

#define GC_FRAME(args) \
    GC_OPEN_FRAME args GC_CLOSE_FRAME

#define GC_STATIC_FRAME(args) \
    static GC_FRAME(args)

#define POINTER(pointer) \
    if (pointer != 0)    \
        f((ManagedObject *&)pointer);

#define LIST(list)                    \
    for (auto &__gc_pointer__ : list) \
        if (__gc_pointer__ != 0)      \
            f((ManagedObject *&)__gc_pointer__);

#define MAP_FIRST(map)              \
    for (auto &__gc_pair__ : map)   \
        if (__gc_pair__.first != 0) \
            f((ManagedObject *&)__gc_pair__.first);

#define MAP_SECOND(map)              \
    for (auto &__gc_pair__ : map)    \
        if (__gc_pair__.second != 0) \
            f((ManagedObject *&)__gc_pair__.second);
