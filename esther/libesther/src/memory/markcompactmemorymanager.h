#pragma once

#include "memory/memorymanager.h"
#include "common/bytearray.h"

class MarkCompactMemoryManager : public MemoryManager {
    ByteArray memory;
    int objectCount, delta;

public:
    MarkCompactMemoryManager();
    ~MarkCompactMemoryManager();

    ManagedObject *allocate(uint size, int count) override;
    void free(ManagedObject *p) override;

    void collectGarbage() override;
    void reallocate() override;

private:
    void initialize();
    void finalize();

    void updatePointers();
    void updatePointer(ManagedObject *&pointer);

    void mark();
    void compact();

    void updatePointers(ManagedObject *object);
    void forwardPointers(ManagedObject *object);
    void mark(ManagedObject *object);
};

inline void MarkCompactMemoryManager::updatePointer(ManagedObject *&pointer) {
    pointer = (ManagedObject *)((byte *)pointer + delta);
}
