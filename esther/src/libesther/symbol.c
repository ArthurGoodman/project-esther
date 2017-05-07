#include "esther/symbol.h"

#include "esther/esther.h"
#include "esther/lexer.h"
#include "esther/std_string.h"
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

Object *Symbol_virtual_inspect(Esther *es, Object *self) {
    const char *value = idToString(as_Symbol(self)->id);

    if (strlen(value) == 0)
        return String_new(es, ":\"\"");

    Object *str = String_new(es, ":");

    if (Lexer_isOneToken(es, es->lexer, value))
        String_append_c_str(str, value);
    else {
        String_append_char(str, '\"');

        struct std_string *escaped = std_string_escape(value);
        String_append_c_str(str, std_string_c_str(escaped));
        std_string_delete(escaped);

        String_append_char(str, '\"');
    }

    return str;
}

bool Symbol_virtual_equals(Object *self, Object *obj) {
    return Object_getType(obj) == TSymbol && as_Symbol(self)->id == as_Symbol(obj)->id;
}
