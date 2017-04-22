#include "esther/string.h"

#include "esther/esther.h"
#include "esther/std_string.h"

String *String_new(Esther *esther) {
    return String_new_init(esther, "");
}

String *String_new_init(Esther *esther, const char *value) {
    String *self = malloc(sizeof(String));
    String_init(esther, self, value);
    return self;
}

String *String_new_init_std(Esther *esther, struct std_string *value) {
    String *self = malloc(sizeof(String));
    String_init_std(esther, self, value);
    return self;
}

void String_init(Esther *esther, String *self, const char *value) {
    Object_init(esther, &self->base, esther->stringClass);

    self->value = std_string_new_init(value);

    self->base.toString = String_virtual_toString;
}

void String_init_std(Esther *esther, String *self, struct std_string *value) {
    Object_init(esther, &self->base, esther->stringClass);

    self->value = value;

    self->base.toString = String_virtual_toString;
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

String *String_virtual_toString(Esther *esther, Object *self) {
    UNUSED(esther);
    return (String *)self;
}
