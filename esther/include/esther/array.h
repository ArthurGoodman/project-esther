#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/object.h"

struct std_vector;

typedef struct Array {
    Object base;

    struct std_vector *data;
} Array;

Array *Array_new(Esther *esther);
Array *Array_new_init(Esther *esther, Object *const *data, size_t size);
Array *Array_new_init_std(Esther *esther, struct std_vector *data);
Array *Array_new_init_va(Esther *esther, size_t size, ...);

void Array_init(Esther *esther, Array *self, Object *const *data, size_t size);
void Array_init_std(Esther *esther, Array *self, struct std_vector *vector);

size_t Array_size(Array *self);

Object *Array_get(Array *self, size_t index);
void Array_set(Array *self, size_t index, Object *value);

void Array_append(Array *self, Array *array);
void Array_append_std(Array *self, struct std_vector *vector);

void Array_push(Array *self, Object *value);
Object *Array_pop(Array *self);

String *Array_virtual_inspect(Esther *esther, Object *self);

#ifdef __cplusplus
}
#endif
