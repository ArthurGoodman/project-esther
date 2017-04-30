#include "esther/array.h"

#include <string.h>

#include "esther/esther.h"
#include "esther/std_vector.h"
#include "esther/string.h"

Object *Array_new(Esther *es, size_t size, ...) {
    va_list ap;
    va_start(ap, size);

    Object *self = gc_alloc(sizeof(Array));
    Array_init_va(es, self, size, ap);

    va_end(ap);

    return self;
}

Object *Array_new_init(Esther *es, Object *const *data, size_t size) {
    Object *self = gc_alloc(sizeof(Array));
    Array_init(es, self, data, size);
    return self;
}

Object *Array_new_init_std(Esther *es, struct std_vector *data) {
    Object *self = gc_alloc(sizeof(Array));
    Array_init_std(es, self, data);
    return self;
}

void Array_init(Esther *es, Object *self, Object *const *data, size_t size) {
    Array_init_std(es, self, std_vector_new_init((void **)data, size));
}

void Array_init_std(Esther *es, Object *self, struct std_vector *data) {
    Object_init(es, self, TArray, es->arrayClass);

    as_Array(self)->data = data;

    as_Array(self)->base.toString = Array_virtual_inspect;
    as_Array(self)->base.inspect = Array_virtual_inspect;

    self->base.base.mapOnReferences = Array_virtual_mapOnReferences;
    self->base.finalize = Array_virtual_finalize;
}

void Array_init_va(Esther *es, Object *self, size_t size, va_list ap) {
    struct std_vector *data = std_vector_new();

    std_vector_resize(data, size);

    for (size_t i = 0; i < size; i++)
        std_vector_set(data, i, va_arg(ap, Object *));

    Array_init_std(es, self, data);
}

size_t Array_size(Object *self) {
    return std_vector_size(as_Array(self)->data);
}

Object *Array_get(Object *self, size_t index) {
    return std_vector_at(as_Array(self)->data, index);
}

void Array_set(Object *self, size_t index, Object *value) {
    std_vector_set(as_Array(self)->data, index, value);
}

void Array_append(Object *self, Object *array) {
    std_vector_append(as_Array(self)->data, as_Array(array)->data);
}

void Array_append_std(Object *self, struct std_vector *vector) {
    std_vector_append(as_Array(self)->data, vector);
}

void Array_push(Object *self, Object *value) {
    std_vector_push(as_Array(self)->data, value);
}

Object *Array_pop(Object *self) {
    return std_vector_pop(as_Array(self)->data);
}

Object *Array_virtual_inspect(Esther *es, Object *self) {
    struct std_vector *data = as_Array(self)->data;
    size_t size = std_vector_size(data);

    Object *str = String_new(es, "[");

    for (size_t i = 0; i < size; i++) {
        String_append(str, Object_inspect(es, std_vector_at(data, i)));

        if (i < size - 1)
            String_append_c_str(str, ", ");
    }

    String_append_c_str(str, "]");

    return str;
}

void Array_virtual_mapOnReferences(Mapper *self, MapFunction f) {
    Object_virtual_mapOnReferences(self, f);

    for (size_t i = 0; i < std_vector_size(as_Array(self)->data); i++) {
        void *value = std_vector_at(as_Array(self)->data, i);
        f((void **)&value);
        std_vector_set(as_Array(self)->data, i, value);
    }
}

void Array_virtual_finalize(ManagedObject *self) {
    Object_virtual_finalize(self);

    std_vector_delete(as_Array(self)->data);
}
