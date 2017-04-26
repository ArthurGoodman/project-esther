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

#define as_tuple(obj) ((Tuple *)(obj))

Object *Tuple_new(Esther *esther, size_t size, ...);
Object *Tuple_new_init(Esther *esther, Object *const *data, size_t size);
Object *Tuple_new_init_null(Esther *esther, size_t size);

void Tuple_init(Esther *esther, Object *self, Object *const *data, size_t size);
void Tuple_init_null(Esther *esther, Object *self, size_t size);
void Tuple_init_va(Esther *esther, Object *self, size_t size, va_list ap);

size_t Tuple_size(Object *self);

Object *Tuple_get(Object *self, size_t index);
void Tuple_set(Object *self, size_t index, Object *value);

Object *Tuple_virtual_inspect(Esther *esther, Object *self);

#ifdef __cplusplus
}
#endif
