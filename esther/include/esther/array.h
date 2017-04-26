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

#define as_array(obj) ((Array *)(obj))

Object *Array_new(Esther *esther, size_t size, ...);
Object *Array_new_init(Esther *esther, Object *const *data, size_t size);
Object *Array_new_init_std(Esther *esther, struct std_vector *data);

void Array_init(Esther *esther, Object *self, Object *const *data, size_t size);
void Array_init_std(Esther *esther, Object *self, struct std_vector *data);
void Array_init_va(Esther *esther, Object *self, size_t size, va_list ap);

size_t Array_size(Object *self);

Object *Array_get(Object *self, size_t index);
void Array_set(Object *self, size_t index, Object *value);

void Array_append(Object *self, Object *array);
void Array_append_std(Object *self, struct std_vector *vector);

void Array_push(Object *self, Object *value);
Object *Array_pop(Object *self);

Object *Array_virtual_inspect(Esther *esther, Object *self);

#ifdef __cplusplus
}
#endif
