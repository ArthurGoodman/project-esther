#include "esther/array.h"

#include <string.h>

#include "esther/esther.h"
#include "esther/std_vector.h"
#include "esther/string.h"

Object *Array_new(Esther *esther, size_t size, ...) {
    va_list ap;
    va_start(ap, size);

    Object *self = malloc(sizeof(Array));
    Array_init_va(esther, self, size, ap);

    va_end(ap);

    return self;
}

Object *Array_new_init(Esther *esther, Object *const *data, size_t size) {
    Object *self = malloc(sizeof(Array));
    Array_init(esther, self, data, size);
    return self;
}

Object *Array_new_init_std(Esther *esther, struct std_vector *data) {
    Object *self = malloc(sizeof(Array));
    Array_init_std(esther, self, data);
    return self;
}

void Array_init(Esther *esther, Object *self, Object *const *data, size_t size) {
    Array_init_std(esther, self, std_vector_new_init((void **)data, size));
}

void Array_init_std(Esther *esther, Object *self, struct std_vector *data) {
    Object_init(esther, self, esther->arrayClass);

    as_array(self)->data = data;

    as_array(self)->base.toString = Array_virtual_inspect;
    as_array(self)->base.inspect = Array_virtual_inspect;
}

void Array_init_va(Esther *esther, Object *self, size_t size, va_list ap) {
    struct std_vector *data = std_vector_new();

    std_vector_resize(data, size);

    for (size_t i = 0; i < size; i++)
        std_vector_set(data, i, va_arg(ap, Object *));

    Array_init_std(esther, self, data);
}

size_t Array_size(Object *self) {
    return std_vector_size(as_array(self)->data);
}

Object *Array_get(Object *self, size_t index) {
    return std_vector_at(as_array(self)->data, index);
}

void Array_set(Object *self, size_t index, Object *value) {
    std_vector_set(as_array(self)->data, index, value);
}

void Array_append(Object *self, Object *array) {
    std_vector_append(as_array(self)->data, as_array(array)->data);
}

void Array_append_std(Object *self, struct std_vector *vector) {
    std_vector_append(as_array(self)->data, vector);
}

void Array_push(Object *self, Object *value) {
    std_vector_push(as_array(self)->data, value);
}

Object *Array_pop(Object *self) {
    return std_vector_pop(as_array(self)->data);
}

Object *Array_virtual_inspect(Esther *esther, Object *self) {
    struct std_vector *data = as_array(self)->data;
    size_t size = std_vector_size(data);

    Object *str = String_new(esther, "[");

    for (size_t i = 0; i < size; i++) {
        String_append(str, Object_inspect(esther, std_vector_at(data, i)));

        if (i < size - 1)
            String_append_c_str(str, ", ");
    }

    String_append_c_str(str, "]");

    return str;
}
