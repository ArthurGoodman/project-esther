#include "esther/tuple.h"

#include <string.h>

#include "esther/esther.h"
#include "esther/std_string.h"
#include "esther/string.h"

Object *Tuple_new(Esther *esther, size_t size, ...) {
    va_list ap;
    va_start(ap, size);

    Object *self = malloc(sizeof(Tuple));
    Tuple_init_va(esther, self, size, ap);

    va_end(ap);

    return self;
}

Object *Tuple_new_init(Esther *esther, Object *const *data, size_t size) {
    Object *self = malloc(sizeof(Tuple));
    Tuple_init(esther, self, data, size);
    return self;
}

Object *Tuple_new_init_null(Esther *esther, size_t size) {
    Object *self = malloc(sizeof(Tuple));
    Tuple_init_null(esther, self, size);
    return self;
}

void Tuple_init(Esther *esther, Object *self, Object *const *data, size_t size) {
    Tuple_init_null(esther, self, size);
    memcpy(as_tuple(self)->data, data, size * sizeof(Object *));
}

void Tuple_init_null(Esther *esther, Object *self, size_t size) {
    Object_init(esther, self, esther->tupleClass);

    as_tuple(self)->data = malloc(size * sizeof(Object *));
    memset(as_tuple(self)->data, 0, size * sizeof(Object *));

    as_tuple(self)->size = size;

    as_tuple(self)->base.toString = Tuple_virtual_inspect;
    as_tuple(self)->base.inspect = Tuple_virtual_inspect;
}

void Tuple_init_va(Esther *esther, Object *self, size_t size, va_list ap) {
    Tuple_init_null(esther, self, size);

    for (size_t i = 0; i < size; i++)
        as_tuple(self)->data[i] = va_arg(ap, Object *);
}

size_t Tuple_size(Object *self) {
    return as_tuple(self)->size;
}

Object *Tuple_get(Object *self, size_t index) {
    return as_tuple(self)->data[index];
}

void Tuple_set(Object *self, size_t index, Object *value) {
    as_tuple(self)->data[index] = value;
}

Object *Tuple_virtual_inspect(Esther *esther, Object *self) {
    Object **data = as_tuple(self)->data;
    size_t size = as_tuple(self)->size;

    Object *str = String_new(esther, "(");

    for (size_t i = 0; i < size; i++) {
        String_append(str, Object_inspect(esther, data[i]));

        if (i < size - 1)
            String_append_c_str(str, ", ");
    }

    String_append_c_str(str, ")");

    return str;
}
