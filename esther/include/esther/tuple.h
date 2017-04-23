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

Tuple *Tuple_new(Esther *esther);
Tuple *Tuple_new_init(Esther *esther, Object *const *data, size_t size);

void Tuple_init(Esther *esther, Tuple *self, Object *const *data, size_t size);

size_t Tuple_size(Tuple *self);

Object *Tuple_get(Tuple *self, size_t index);
void Tuple_set(Tuple *self, size_t index, Object *value);

String *Tuple_virtual_inspect(Esther *esther, Object *self);

#ifdef __cplusplus
}
#endif
