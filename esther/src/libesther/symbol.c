#include "esther/symbol.h"

#include "esther/esther.h"
//#include "esther/lexer.h"
#include "esther/std_string.h"
#include "esther/string.h"

Object *Symbol_new(Esther *es, struct string name) {
    Object *self = gc_alloc(sizeof(Symbol));
    Symbol_init(es, self, name);
    return self;
}

static VTableForObject Symbol_vtable = {
    .base = {
        .base = {
            .mapOnReferences = Object_virtual_mapOnReferences },
        .finalize = Object_virtual_finalize },
    .toString = Symbol_virtual_toString,
    .inspect = Symbol_virtual_inspect,
    .equals = Symbol_virtual_equals,
    .isTrue = Object_virtual_isTrue
};

void Symbol_init(Esther *es, Object *self, struct string name) {
    Object_init(es, self, TSymbol, es->symbolClass);

    as_Symbol(self)->id = str_to_id(name);

    *(void **) self = &Symbol_vtable;
}

Id Symbol_getId(Object *self) {
    return as_Symbol(self)->id;
}

Object *Symbol_virtual_toString(Esther *es, Object *self) {
    return String_new(es, id_to_str(as_Symbol(self)->id));
}

Object *Symbol_virtual_inspect(Esther *es, Object *self) {
    struct string value = id_to_str(as_Symbol(self)->id);

    if (value.size == 0)
        return String_new_c_str(es, ":\"\"");

    Object *str = String_new_c_str(es, ":");

    // @Temporary solution: no one-token check

    // if (Lexer_isOneToken(es, es->lexer, value))
    //     String_append_c_str(str, value);
    // else {
    String_append_char(str, '\"');

    struct string escaped = string_escape(as_String(self)->value);
    String_append_std(str, escaped);
    string_free(&escaped);

    String_append_char(str, '\"');
    // }

    return str;
}

bool Symbol_virtual_equals(Object *self, Object *obj) {
    return Object_getType(obj) == TSymbol && as_Symbol(self)->id == as_Symbol(obj)->id;
}
