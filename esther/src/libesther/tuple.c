#include "esther/tuple.h"

#include <string.h>

#include "esther/esther.h"
#include "esther/string.h"
#include "esther/std_string.h"

Tuple *Tuple_new(Esther *esther) {
    return Tuple_new_init(esther, NULL, 0);
}

Tuple *Tuple_new_init(Esther *esther, Object *const *data, size_t size) {
    Tuple *self = malloc(sizeof(Tuple));
    Tuple_init(esther, self, data, size);
    return self;
}

void Tuple_init(Esther *esther, Tuple *self, Object *const *data, size_t size) {
    Object_init(esther, &self->base, esther->tupleClass);

    self->data = malloc(sizeof(Object *) * size);
    memcpy(self->data, data, sizeof(Object *) * size);

    self->size = size;

    self->base.toString = Tuple_virtual_toString;
}

size_t Tuple_size(Tuple *self) {
    return self->size;
}

Object *Tuple_get(Tuple *self, size_t index) {
    return self->data[index];
}

void Tuple_set(Tuple *self, size_t index, Object *value) {
    self->data[index] = value;
}

String *Tuple_virtual_toString(Esther *esther, Object *self) {
    Object **data = ((Tuple *)self)->data;
    size_t size = ((Tuple *)self)->size;

    String *str = String_new_init(esther, "(");

    for (size_t i = 0; i < size; i++) {
        String_append(str, Object_toString(esther, data[i]));

        if (i < size - 1)
            String_append_c_str(str, ", ");
    }

    String_append_c_str(str, ")");

    return str;
}
