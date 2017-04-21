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

void String_init(Esther *esther, String *self, const char *value) {
    Object_init(esther, &self->base, esther->stringClass);
    self->value = std_string_new_init(value);
}

const char *String_c_str(String *self) {
    return std_string_c_str(self->value);
}
