#include "esther/symbol.h"

#include "esther/esther.h"
#include "esther/string.h"

Object *Symbol_new(Esther *es, const char *name) {
    Object *self = gc_alloc(sizeof(Symbol));
    Symbol_init(es, self, name);
    return self;
}

void Symbol_init(Esther *es, Object *self, const char *name) {
    Object_init(es, self, TSymbol, es->symbolClass);

    as_Symbol(self)->id = stringToId(name);

    as_Symbol(self)->base.toString = Symbol_virtual_toString;
    as_Symbol(self)->base.inspect = Symbol_virtual_inspect;
    as_Symbol(self)->base.equals = Symbol_virtual_equals;
}

Id Symbol_getId(Object *self) {
    return as_Symbol(self)->id;
}

Object *Symbol_virtual_toString(Esther *es, Object *self) {
    return String_new(es, idToString(as_Symbol(self)->id));
}

// @TODO: Implement proper inspection with escaping
Object *Symbol_virtual_inspect(Esther *es, Object *self) {
    const char *value = idToString(as_Symbol(self)->id);

    if (strlen(value) == 0)
        return String_new(es, ":\"\"");

    Object *str = String_new(es, ":");

    if (isalpha(value[0]))
        String_append_c_str(str, value);
    else {
        String_append_c_str(str, "\"");
        String_append_c_str(str, value);
        String_append_c_str(str, "\"");
    }

    return str;
}

bool Symbol_virtual_equals(Object *self, Object *obj) {
    return Object_getType(obj) == TSymbol && as_Symbol(self)->id == as_Symbol(obj)->id;
}
