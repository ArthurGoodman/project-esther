#include "esther/symbol.h"

#include "esther/esther.h"
#include "esther/lexer.h"
#include "esther/std_map.h"
#include "esther/std_string.h"
#include "esther/string.h"

static struct std_map *idSymbol = NULL;

Object *id_to_sym(Esther *es, ID id) {
    if (!is_valid_id(id))
        return NULL;

    if (!idSymbol || !std_map_contains(idSymbol, (void *) id)) {
        if (!idSymbol)
            idSymbol = std_map_new(compare_id);

        Object *symbol = Symbol_new(es, id_to_str(id));
        std_map_set(idSymbol, (void *) id, symbol);
        return symbol;
    }

    return std_map_get(idSymbol, (void *) id);
}

Object *str_to_sym(Esther *es, struct string str) {
    return id_to_sym(es, str_to_id(str));
}

Object *c_str_to_sym(Esther *es, const char *str) {
    return id_to_sym(es, c_str_to_id(str));
}

Object *Symbol_new(Esther *es, struct string name) {
    Object *self = gc_alloc(sizeof(Symbol));
    Symbol_init(es, self, name);
    return self;
}

Object *Symbol_new_c_str(Esther *es, const char *name) {
    Object *self = gc_alloc(sizeof(Symbol));
    Symbol_init_c_str(es, self, name);
    return self;
}

static ObjectVTable vtable_for_Symbol = {
    .base = {
        .base = {
            .mapOnRefs = Object_virtual_mapOnRefs },
        .finalize = Object_virtual_finalize },
    .toString = Symbol_virtual_toString,
    .inspect = Symbol_virtual_inspect,
    .equals = Symbol_virtual_equals,
    .less = Symbol_virtual_less,
    .isTrue = Object_virtual_isTrue
};

static void Symbol_init_id(Esther *es, Object *self, ID id) {
    Object_init(es, self, TSymbol, es->symbolClass);

    as_Symbol(self)->id = id;

    *(void **) self = &vtable_for_Symbol;
}

Object *Symbol_new_id(Esther *es, ID id) {
    if (!is_valid_id(id))
        return NULL;

    Object *self = gc_alloc(sizeof(Symbol));
    Symbol_init_id(es, self, id);
    return self;
}

void Symbol_init(Esther *es, Object *self, struct string name) {
    Symbol_init_id(es, self, str_to_id(name));
}

void Symbol_init_c_str(Esther *es, Object *self, const char *name) {
    Symbol_init_id(es, self, c_str_to_id(name));
}

ID Symbol_getId(Object *self) {
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

    if (Lexer_isOneToken(es, es->lexer, value.data))
        String_append_std(str, value);
    else {
        String_append_char(str, '\"');

        struct string escaped = string_escape(value);
        String_append_std(str, escaped);
        string_free(escaped);

        String_append_char(str, '\"');
    }

    return str;
}

bool Symbol_virtual_equals(Object *self, Object *obj) {
    return Object_getType(obj) == TSymbol ? as_Symbol(self)->id == as_Symbol(obj)->id : Object_virtual_equals(self, obj);
}

bool Symbol_virtual_less(Object *self, Object *obj) {
    return Object_getType(obj) == TSymbol ? as_Symbol(self)->id < as_Symbol(obj)->id : Object_virtual_less(self, obj);
}
