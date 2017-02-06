#include "conservativememorymanager.h"

#include <memory>

#include "common/io.h"
#include "common/bytearray.h"

#ifdef MEM_MANAGEMENT

namespace {
es::ByteArray *memory;
size_t objectCount;
}

namespace es {

ConservativeMemoryManager::ConservativeMemoryManager() {
    initialize();
}

ConservativeMemoryManager::~ConservativeMemoryManager() {
    finalize();
}

ManagedObject *ConservativeMemoryManager::allocate(size_t size, size_t count) {
#ifdef VERBOSE_GC
    IO::writeLine("ConservativeMemoryManager::allocate(size=%u)", size);
#endif

    objectCount += count;

    return static_cast<ManagedObject *>(malloc(size));
}

void ConservativeMemoryManager::free(ManagedObject *) {
}

void ConservativeMemoryManager::collectGarbage() {
#ifdef VERBOSE_GC
    IO::writeLine("\nConservativeMemoryManager::collectGarbage()");
    size_t oldSize = memory->getSize(), oldObjectCount = objectCount;
#endif

#ifdef VERBOSE_GC
    IO::writeLine("//freed=%u, freedObjects=%u, objectCount=%u\n", oldSize - memory->getSize(), oldObjectCount - objectCount, objectCount);
#endif
}

void ConservativeMemoryManager::reallocate() {
}

void ConservativeMemoryManager::initialize() {
    memory = new ByteArray(InitialCapacity);
    objectCount = 0;
}

void ConservativeMemoryManager::finalize() {
#ifdef VERBOSE_GC
    IO::writeLine("\nObject count: %u", objectCount);
    IO::writeLine("Memory used: %u", memory->getSize());
    IO::writeLine("Total memory: %u", memory->getCapacity());
    IO::writeLine("\nConservativeMemoryManager::finalize()");
#endif

    delete memory;
}
}

#endif
