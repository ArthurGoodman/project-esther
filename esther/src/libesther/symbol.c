#include "esther/symbol.h"

#include "esther/esther.h"
#include "esther/string.h"

Object *Symbol_new(Esther *es, const char *name) {
    Object *self = malloc(sizeof(Symbol));
    Symbol_init(es, self, name);
    return self;
}

void Symbol_init(Esther *es, Object *self, const char *name) {
    Object_init(es, self, es->symbolClass);

    as_Symbol(self)->id = stringToId(name);

    as_Symbol(self)->base.toString = Symbol_virtual_toString;
    as_Symbol(self)->base.inspect = Symbol_virtual_inspect;
}

Id Symbol_getId(Object *self) {
    return as_Symbol(self)->id;
}

Object *Symbol_virtual_toString(Esther *es, Object *self) {
    return String_new(es, idToString(as_Symbol(self)->id));
}

Object *Symbol_virtual_inspect(Esther *es, Object *self) {
    Object *str = String_new(es, ":");
    String_append_c_str(str, idToString(as_Symbol(self)->id));
    return str;
}
