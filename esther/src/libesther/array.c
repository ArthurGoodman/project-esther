#include "esther/array.h"

#include <string.h>

#include "esther/esther.h"
#include "esther/std_vector.h"
#include "esther/string.h"

Array *Array_new(Esther *esther) {
    return Array_new_init(esther, NULL, 0);
}

Array *Array_new_init(Esther *esther, Object *const *data, size_t size) {
    Array *self = malloc(sizeof(Array));
    Array_init(esther, self, data, size);
    return self;
}

Array *Array_new_init_std(Esther *esther, struct std_vector *data) {
    Array *self = malloc(sizeof(Array));
    Array_init_std(esther, self, data);
    return self;
}

void Array_init(Esther *esther, Array *self, Object *const *data, size_t size) {
    Array_init_std(esther, self, std_vector_new_init((void **)data, size));
}

void Array_init_std(Esther *esther, Array *self, struct std_vector *data) {
    Object_init(esther, &self->base, esther->arrayClass);

    self->data = data;

    self->base.toString = Array_virtual_inspect;
    self->base.inspect = Array_virtual_inspect;
}

size_t Array_size(Array *self) {
    return std_vector_size(self->data);
}

Object *Array_get(Array *self, size_t index) {
    return std_vector_at(self->data, index);
}

void Array_set(Array *self, size_t index, Object *value) {
    std_vector_set(self->data, index, value);
}

void Array_append(Array *self, Array *array) {
    std_vector_append(self->data, array->data);
}

void Array_append_std(Array *self, struct std_vector *vector) {
    std_vector_append(self->data, vector);
}

void Array_push(Array *self, Object *value) {
    std_vector_push(self->data, value);
}

Object *Array_pop(Array *self) {
    return std_vector_pop(self->data);
}

String *Array_virtual_inspect(Esther *esther, Object *self) {
    struct std_vector *data = ((Array *)self)->data;
    size_t size = std_vector_size(data);

    String *str = String_new_init(esther, "[");

    for (size_t i = 0; i < size; i++) {
        String_append(str, Object_inspect(esther, std_vector_at(data, i)));

        if (i < size - 1)
            String_append_c_str(str, ", ");
    }

    String_append_c_str(str, "]");

    return str;
}
