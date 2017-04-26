#include "esther/string.h"

#include "esther/esther.h"
#include "esther/std_string.h"

Object *String_new(Esther *esther, const char *value) {
    Object *self = malloc(sizeof(String));
    String_init(esther, self, value);
    return self;
}

Object *String_new_std(Esther *esther, struct std_string *value) {
    Object *self = malloc(sizeof(String));
    String_init_std(esther, self, value);
    return self;
}

void String_init(Esther *esther, Object *self, const char *value) {
    String_init_std(esther, self, std_string_new_init(value));
}

void String_init_std(Esther *esther, Object *self, struct std_string *value) {
    Object_init(esther, self, esther->stringClass);

    as_string(self)->value = value;

    as_string(self)->base.toString = String_virtual_toString;
    as_string(self)->base.inspect = String_virtual_inspect;
    as_string(self)->base.equals = String_virtual_equals;
}

const char *String_c_str(Object *self) {
    return std_string_c_str(as_string(self)->value);
}

void String_append(Object *self, Object *str) {
    std_string_append(as_string(self)->value, as_string(str)->value);
}

void String_append_c_str(Object *self, const char *str) {
    std_string_append_c_str(as_string(self)->value, str);
}

Object *String_virtual_toString(Esther *UNUSED(esther), Object *self) {
    return self;
}

Object *String_virtual_inspect(Esther *esther, Object *self) {
    Object *str = String_new(esther, "\"");
    String_append(str, self);
    String_append_c_str(str, "\"");

    return str;
}

bool String_virtual_equals(Esther *esther, Object *self, Object *obj) {
    return Object_is(obj, esther->stringClass) && std_string_equals(as_string(self)->value, as_string(obj)->value);
}
