#include "esther/symbol.h"

#include "esther/esther.h"
#include "esther/string.h"

Symbol *Symbol_new(Esther *esther, const char *name) {
    Symbol *self = malloc(sizeof(Symbol));
    Symbol_init(esther, self, name);
    return self;
}

void Symbol_init(Esther *esther, Symbol *self, const char *name) {
    Object_init(esther, &self->base, esther->symbolClass);

    self->id = stringToId(name);

    self->base.toString = Symbol_virtual_toString;
    self->base.inspect = Symbol_virtual_inspect;
}

String *Symbol_virtual_toString(Esther *esther, Object *self) {
    return String_new_init(esther, idToString(((Symbol *)self)->id));
}

String *Symbol_virtual_inspect(Esther *esther, Object *self) {
    String *str = String_new_init(esther, ":");
    String_append_c_str(str, idToString(((Symbol *)self)->id));
    return str;
}
