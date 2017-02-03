//#pragma once

//#include "common/bytearray.h"

//class ManagedObject;

//class SemispaceMemoryManager {
//    static const int InitialCapacity = 1 << 10;

//    ByteArray memory;
//    int objectCount, memoryUsed, capacity, delta;

//    byte *toSpace, *fromSpace, *allocPtr;

//public:
//    SemispaceMemoryManager();
//    ~SemispaceMemoryManager();

//    static ManagedObject *allocate(uint size, int count = 1);
//    static void free(ManagedObject *p);

//    static void collectGarbage();
//    static void reallocate();

//private:
//    void initialize();
//    void finalize();

//    bool enoughSpace(int size) const;

//    ManagedObject *copy(ManagedObject *object);
//    void expand();
//};
