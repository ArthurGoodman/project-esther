#include "esther/string.h"

#include "esther/esther.h"
#include "esther/std_string.h"

String *String_new(Esther *esther, const char *value) {
    String *self = malloc(sizeof(String));
    String_init(esther, self, value);
    return self;
}

String *String_new_std(Esther *esther, struct std_string *value) {
    String *self = malloc(sizeof(String));
    String_init_std(esther, self, value);
    return self;
}

void String_init(Esther *esther, String *self, const char *value) {
    String_init_std(esther, self, std_string_new_init(value));
}

void String_init_std(Esther *esther, String *self, struct std_string *value) {
    Object_init(esther, &self->base, esther->stringClass);

    self->value = value;

    self->base.toString = String_virtual_toString;
    self->base.inspect = String_virtual_inspect;
    self->base.equals = String_virtual_equals;
}

const char *String_c_str(String *self) {
    return std_string_c_str(self->value);
}

void String_append(String *self, String *str) {
    std_string_append(self->value, str->value);
}

void String_append_c_str(String *self, const char *str) {
    std_string_append_c_str(self->value, str);
}

String *String_virtual_toString(Esther *UNUSED(esther), Object *self) {
    return (String *)self;
}

String *String_virtual_inspect(Esther *esther, Object *self) {
    String *str = String_new(esther, "\"");
    String_append(str, (String *)self);
    String_append_c_str(str, "\"");

    return str;
}

bool String_virtual_equals(Esther *esther, Object *self, Object *obj) {
    return Object_is(obj, esther->stringClass) && std_string_equals(((String *)self)->value, ((String *)obj)->value);
}
