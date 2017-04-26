#include "esther/symbol.h"

#include "esther/esther.h"
#include "esther/string.h"

Object *Symbol_new(Esther *esther, const char *name) {
    Object *self = malloc(sizeof(Symbol));
    Symbol_init(esther, self, name);
    return self;
}

void Symbol_init(Esther *esther, Object *self, const char *name) {
    Object_init(esther, self, esther->symbolClass);

    as_symbol(self)->id = stringToId(name);

    as_symbol(self)->base.toString = Symbol_virtual_toString;
    as_symbol(self)->base.inspect = Symbol_virtual_inspect;
}

Id Symbol_getId(Object *self) {
    return as_symbol(self)->id;
}

Object *Symbol_virtual_toString(Esther *esther, Object *self) {
    return String_new(esther, idToString(as_symbol(self)->id));
}

Object *Symbol_virtual_inspect(Esther *esther, Object *self) {
    Object *str = String_new(esther, ":");
    String_append_c_str(str, idToString(as_symbol(self)->id));
    return str;
}
