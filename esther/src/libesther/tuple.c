#include "esther/tuple.h"

#include "esther/esther.h"
#include "esther/std_string.h"
#include "esther/string.h"

Object *Tuple_new(Esther *es, size_t size, ...) {
    va_list ap;
    va_start(ap, size);

    Object *self = gc_alloc(sizeof(Tuple));
    Tuple_init_va(es, self, size, ap);

    va_end(ap);

    return self;
}

Object *Tuple_new_init(Esther *es, Object *const *data, size_t size) {
    Object *self = gc_alloc(sizeof(Tuple));
    Tuple_init(es, self, data, size);
    return self;
}

Object *Tuple_new_init_null(Esther *es, size_t size) {
    Object *self = gc_alloc(sizeof(Tuple));
    Tuple_init_null(es, self, size);
    return self;
}

void Tuple_init(Esther *es, Object *self, Object *const *data, size_t size) {
    Tuple_init_null(es, self, size);
    memcpy(as_Tuple(self)->data, data, size * sizeof(Object *));
}

static VTableForObject Tuple_vtable = {
    .base = {
        .base = {
            .mapOnRefs = Tuple_virtual_mapOnRefs },
        .finalize = Tuple_virtual_finalize },
    .toString = Tuple_virtual_inspect,
    .inspect = Tuple_virtual_inspect,
    .equals = Object_virtual_equals,
    .less = Object_virtual_less,
    .isTrue = Object_virtual_isTrue
};

void Tuple_init_null(Esther *es, Object *self, size_t size) {
    Object_init(es, self, TTuple, es->tupleClass);

    as_Tuple(self)->data = calloc(size, sizeof(Object *));

    as_Tuple(self)->size = size;

    *(void **) self = &Tuple_vtable;
}

void Tuple_init_va(Esther *es, Object *self, size_t size, va_list ap) {
    Tuple_init_null(es, self, size);

    for (size_t i = 0; i < size; i++)
        as_Tuple(self)->data[i] = va_arg(ap, Object *);
}

size_t Tuple_size(Object *self) {
    return as_Tuple(self)->size;
}

Object *Tuple_get(Object *self, size_t index) {
    return as_Tuple(self)->data[index];
}

void Tuple_set(Object *self, size_t index, Object *value) {
    as_Tuple(self)->data[index] = value;
}

Object *Tuple_virtual_inspect(Esther *es, Object *self) {
    Object *str = String_new_c_str(es, "(");

    for (size_t i = 0; i < as_Tuple(self)->size; i++) {
        String_append(str, Object_inspect(es, as_Tuple(self)->data[i]));

        if (i < as_Tuple(self)->size - 1)
            String_append_c_str(str, ", ");
    }

    String_append_c_str(str, ")");

    return str;
}

void Tuple_virtual_mapOnRefs(Mapper *self, MapFunction f) {
    Object_virtual_mapOnRefs(self, f);

    for (size_t i = 0; i < as_Tuple(self)->size; i++)
        f(as_Tuple(self)->data[i]);
}

void Tuple_virtual_finalize(ManagedObject *self) {
    Object_virtual_finalize(self);

    free(as_Tuple(self)->data);
}
