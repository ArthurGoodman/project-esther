#include "esther/string.h"

#include "esther/esther.h"
#include "esther/std_string.h"

Object *String_new(Esther *es, const char *value) {
    Object *self = malloc(sizeof(String));
    String_init(es, self, value);
    return self;
}

Object *String_new_std(Esther *es, struct std_string *value) {
    Object *self = malloc(sizeof(String));
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
}

const char *String_c_str(Object *self) {
    return std_string_c_str(as_String(self)->value);
}

void String_append(Object *self, Object *str) {
    std_string_append(as_String(self)->value, as_String(str)->value);
}

void String_append_c_str(Object *self, const char *str) {
    std_string_append_c_str(as_String(self)->value, str);
}

void String_append_char(Object *self, char c) {
    std_string_append_char(as_String(self)->value, c);
}

size_t String_size(Object *self) {
    return std_string_size(as_String(self)->value);
}

Object *String_virtual_toString(Esther *UNUSED(es), Object *self) {
    return self;
}

Object *String_virtual_inspect(Esther *es, Object *self) {
    Object *str = String_new(es, "\"");
    String_append(str, self);
    String_append_c_str(str, "\"");

    return str;
}

bool String_virtual_equals(Object *self, Object *obj) {
    return Object_getType(obj) == TString && std_string_equals(as_String(self)->value, as_String(obj)->value);
}
