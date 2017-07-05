#include "esther/string.h"

#include "esther/esther.h"
#include "esther/std_string.h"

Object *String_new(Esther *es, struct string value) {
    Object *self = gc_alloc(sizeof(String));
    String_init(es, self, value);
    return self;
}

Object *String_new_move(Esther *es, struct string value) {
    Object *self = gc_alloc(sizeof(String));
    String_init_move(es, self, value);
    return self;
}

Object *String_new_c_str(Esther *es, const char *value) {
    Object *self = gc_alloc(sizeof(String));
    String_init_c_str(es, self, value);
    return self;
}

static VTableForObject String_vtable = {
    .base = {
        .base = {
            .mapOnReferences = Object_virtual_mapOnReferences },
        .finalize = String_virtual_finalize },
    .toString = String_virtual_toString,
    .inspect = String_virtual_inspect,
    .equals = String_virtual_equals,
    .isTrue = Object_virtual_isTrue
};

void String_init(Esther *es, Object *self, struct string value) {
    String_init_move(es, self, string_copy(value));
}

void String_init_move(Esther *es, Object *self, struct string value) {
    Object_init(es, self, TString, es->stringClass);

    as_String(self)->value = value;

    *(void **) self = &String_vtable;
}

void String_init_c_str(Esther *es, Object *self, const char *value) {
    String_init_move(es, self, string_new_c_str(value));
}

const char *String_c_str(Object *self) {
    return as_String(self)->value.data;
}

struct string String_value(Object *self) {
    return as_String(self)->value;
}

Object *String_append(Object *self, Object *str) {
    string_append(&as_String(self)->value, as_String(str)->value);
    return self;
}

Object *String_append_c_str(Object *self, const char *str) {
    string_append_c_str(&as_String(self)->value, str);
    return self;
}

Object *String_append_char(Object *self, char c) {
    string_append_char(&as_String(self)->value, c);
    return self;
}

size_t String_size(Object *self) {
    return as_String(self)->value.size;
}

bool String_contains(Object *self, char c) {
    return string_find_char(as_String(self)->value, c) != (size_t) -1;
}

Object *String_virtual_toString(Esther *UNUSED(es), Object *self) {
    return self;
}

Object *String_virtual_inspect(Esther *es, Object *self) {
    Object *str = String_new_c_str(es, "\"");

    // struct string escaped = string_escape(&as_String(self)->value);
    // String_append_c_str(str, escaped.data);
    // string_free(&escaped);

    // @Temporary solution
    String_append_c_str(str, as_String(self)->value.data);

    String_append_c_str(str, "\"");

    return str;
}

bool String_virtual_equals(Object *self, Object *obj) {
    return Object_getType(obj) == TString && string_equals(as_String(self)->value, as_String(obj)->value);
}

void String_virtual_finalize(ManagedObject *self) {
    Object_virtual_finalize(self);

    string_free(&as_String(self)->value);
}
