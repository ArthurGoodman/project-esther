#include "esther/string.h"

#include "esther/esther.h"
#include "esther/str.h"

PString String_new(struct Esther *esther) {
    return String_new_init(esther, "");
}

PString String_new_init(struct Esther *esther, const char *value) {
    PString self = malloc(sizeof(struct String));
    String_init(esther, self, value);
    return self;
}

void String_init(struct Esther *esther, PString self, const char *value) {
    Object_init(esther, &self->base, esther->stringClass);
    self->value = string_new_init(value);
}

const char *String_c_str(PString self) {
    return string_c_str(self->value);
}
