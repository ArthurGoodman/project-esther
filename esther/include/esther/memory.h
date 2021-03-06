#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

#if defined(__x86_64)
typedef uint64_t ptr_t;
#elif defined(__i386)
typedef uint32_t ptr_t;
#endif

typedef ptr_t *ptr_ptr_t;

typedef struct ManagedObject ManagedObject;
typedef struct Mapper Mapper;

typedef void (*MapFunction)(void *);

typedef struct MapperVTable {
    void (*mapOnRefs)(Mapper *self, MapFunction f);
} MapperVTable;

typedef struct Mapper {
    const void *vtable;
} Mapper;

void Mapper_init(Mapper *self);

void Mapper_mapOnRefs(Mapper *self, MapFunction f);

void Mapper_virtual_mapOnRefs(Mapper *, MapFunction);

typedef struct ManagedObjectVTable {
    MapperVTable base;

    void (*finalize)(ManagedObject *self);
} ManagedObjectVTable;

typedef struct ManagedObject {
    Mapper base;
} ManagedObject;

void ManagedObject_init(ManagedObject *self);

void ManagedObject_finalize(ManagedObject *self);

void ManagedObject_virtual_finalize(ManagedObject *);

void gc_initialize(ptr_ptr_t bp);
void gc_finalize();

void *gc_alloc(size_t size);
void gc_free(void *p);

void gc_collect();

void gc_registerMapper(Mapper *mapper);

#ifdef __cplusplus
}
#endif
