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

#define as_Array(obj) ((Array *)(obj))

Object *Array_new(Esther *es, size_t size, ...);
Object *Array_new_init(Esther *es, Object *const *data, size_t size);
Object *Array_new_init_std(Esther *es, struct std_vector *data);

void Array_init(Esther *es, Object *self, Object *const *data, size_t size);
void Array_init_std(Esther *es, Object *self, struct std_vector *data);
void Array_init_va(Esther *es, Object *self, size_t size, va_list ap);

size_t Array_size(Object *self);

Object *Array_get(Object *self, size_t index);
void Array_set(Object *self, size_t index, Object *value);

void Array_append(Object *self, Object *array);
void Array_append_std(Object *self, struct std_vector *vector);

void Array_push(Object *self, Object *value);
Object *Array_pop(Object *self);

Object *Array_virtual_inspect(Esther *es, Object *self);

void Array_virtual_mapOnReferences(Mapper *self, MapFunction f);
void Array_virtual_finalize(ManagedObject *self);

#ifdef __cplusplus
}
#endif
