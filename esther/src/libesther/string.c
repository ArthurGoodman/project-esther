#include "esther/string.h"

#include "esther/esther.h"

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

void String_init(Esther *es, Object *self, struct string value) {
    String_init_move(es, self, string_copy(value));
}

static ObjectVTable vtable_for_String = {
    .base = {
        .base = {
            .mapOnRefs = Object_virtual_mapOnRefs },
        .finalize = String_virtual_finalize },
    .toString = String_virtual_toString,
    .inspect = String_virtual_inspect,
    .equals = String_virtual_equals,
    .less = String_virtual_less,
    .isTrue = Object_virtual_isTrue,
    .clone = String_virtual_clone
};

void String_init_move(Esther *es, Object *self, struct string value) {
    Object_init(es, self, TString, Esther_getRootObject(es, c_str_to_id("String")));

    as_String(self)->value = value;

    *(void **) self = &vtable_for_String;
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

Object *String_append_std(Object *self, struct string str) {
    string_append(&as_String(self)->value, str);
    return self;
}

size_t String_size(Object *self) {
    return as_String(self)->value.size;
}

size_t String_capacity(Object *self) {
    return as_String(self)->value.capacity;
}

bool String_contains(Object *self, char c) {
    return string_find_char(as_String(self)->value, c, 0) != (size_t) -1;
}

Object *String_virtual_toString(Esther *UNUSED(es), Object *self) {
    return self;
}

Object *String_virtual_inspect(Esther *es, Object *self) {
    Object *str = String_new_c_str(es, "\"");

    struct string escaped = string_escape(as_String(self)->value);
    String_append_std(str, escaped);
    string_free(escaped);

    String_append_c_str(str, "\"");

    return str;
}

bool String_virtual_equals(Object *self, Object *obj) {
    return Object_getType(obj) == TString ? string_equals(as_String(self)->value, as_String(obj)->value) : Object_virtual_equals(self, obj);
}

bool String_virtual_less(Object *self, Object *obj) {
    return Object_getType(obj) == TString ? string_compare(as_String(self)->value, as_String(obj)->value) < 0 : Object_virtual_less(self, obj);
}

Object *String_virtual_clone(Esther *es, Object *self) {
    Object *clone = String_new(es, as_String(self)->value);
    Object_copyAttributes(self, clone);
    return clone;
}

void String_virtual_finalize(ManagedObject *self) {
    Object_virtual_finalize(self);

    string_free(as_String(self)->value);
}
