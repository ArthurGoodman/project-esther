#include "esther/string.h"

#include "esther/esther.h"
#include "esther/std_string.h"

Object *String_new(Esther *es, const char *value) {
    Object *self = gc_alloc(sizeof(String));
    String_init(es, self, value);
    return self;
}

Object *String_new_std(Esther *es, struct std_string *value) {
    Object *self = gc_alloc(sizeof(String));
    String_init_std(es, self, value);
    return self;
}

void String_init(Esther *es, Object *self, const char *value) {
    String_init_std(es, self, std_string_new_init(value));
}

void String_init_std(Esther *es, Object *self, struct std_string *value) {
    Object_init(es, self, TString, es->stringClass);

    as_String(self)->value = value;

    as_String(self)->base.toString = String_virtual_toString;
    as_String(self)->base.inspect = String_virtual_inspect;
    as_String(self)->base.equals = String_virtual_equals;

    self->base.finalize = String_virtual_finalize;
}

const char *String_c_str(Object *self) {
    return std_string_c_str(as_String(self)->value);
}

Object *String_append(Object *self, Object *str) {
    std_string_append(as_String(self)->value, as_String(str)->value);
    return self;
}

Object *String_append_c_str(Object *self, const char *str) {
    std_string_append_c_str(as_String(self)->value, str);
    return self;
}

Object *String_append_char(Object *self, char c) {
    std_string_append_char(as_String(self)->value, c);
    return self;
}

size_t String_size(Object *self) {
    return std_string_size(as_String(self)->value);
}

bool String_contains(Object *self, char c) {
    return std_string_contains(as_String(self)->value, c);
}

Object *String_virtual_toString(Esther *UNUSED(es), Object *self) {
    return self;
}

// @TODO: Impelement escaping
Object *String_virtual_inspect(Esther *es, Object *self) {
    Object *str = String_new(es, "\"");
    String_append(str, self);
    String_append_c_str(str, "\"");

    return str;
}

bool String_virtual_equals(Object *self, Object *obj) {
    return Object_getType(obj) == TString && std_string_equals(as_String(self)->value, as_String(obj)->value);
}

void String_virtual_finalize(ManagedObject *self) {
    Object_virtual_finalize(self);

    std_string_delete(as_String(self)->value);
}
