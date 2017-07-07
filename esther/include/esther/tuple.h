#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/object.h"

typedef struct Tuple {
    Object base;

    Object **data;
    size_t size;
} Tuple;

#define as_Tuple(obj) ((Tuple *) (obj))

Object *Tuple_new(Esther *es, size_t size, ...);
Object *Tuple_new_init(Esther *es, Object *const *data, size_t size);
Object *Tuple_new_init_null(Esther *es, size_t size);

void Tuple_init(Esther *es, Object *self, Object *const *data, size_t size);
void Tuple_init_null(Esther *es, Object *self, size_t size);
void Tuple_init_va(Esther *es, Object *self, size_t size, va_list ap);

size_t Tuple_size(Object *self);

Object *Tuple_get(Object *self, size_t index);
void Tuple_set(Object *self, size_t index, Object *value);

Object *Tuple_virtual_inspect(Esther *es, Object *self);

void Tuple_virtual_mapOnRefs(Mapper *self, MapFunction f);
void Tuple_virtual_finalize(ManagedObject *self);

#ifdef __cplusplus
}
#endif
