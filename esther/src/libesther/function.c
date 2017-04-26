#include "esther/function.h"

#include <string.h>

#include "esther/esther.h"
#include "esther/std_string.h"
#include "esther/string.h"
#include "esther/tuple.h"
#include "esther/context.h"

Object *Function_new(Esther *esther, const char *name, Object *(*body)(), int argc) {
    Object *self = malloc(sizeof(Function));
    Function_init(esther, self, name, body, argc);
    return self;
}

void Function_init(Esther *esther, Object *self, const char *name, Object *(*body)(), int argc) {
    Object_init(esther, self, esther->functionClass);

    as_function(self)->name = strdup(name);
    as_function(self)->body = body;
    as_function(self)->argc = argc;

    as_function(self)->base.toString = Function_virtual_toString;
    as_function(self)->base.inspect = Function_virtual_toString;
}

const char *Function_getName(Object *self) {
    return as_function(self)->name;
}

Object *Function_invoke(Esther *esther, Object *self, Object *selfObject, Object *args) {
    if (as_function(self)->argc == -2)
        return as_function(self)->body(esther, self, selfObject, args);

    if (as_function(self)->argc == -1)
        return as_function(self)->body(esther, selfObject, args);

    if (as_function(self)->argc != (int)Tuple_size(args))
        return NULL;

    switch (as_function(self)->argc) {
    case 0:
        return as_function(self)->body(esther, selfObject);

    case 1:
        return as_function(self)->body(esther, selfObject, Tuple_get(args, 0));

    case 2:
        return as_function(self)->body(esther, selfObject, Tuple_get(args, 0), Tuple_get(args, 1));

    case 3:
        return as_function(self)->body(esther, selfObject, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2));

    case 4:
        return as_function(self)->body(esther, selfObject, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3));

    case 5:
        return as_function(self)->body(esther, selfObject, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3), Tuple_get(args, 4));

    case 6:
        return as_function(self)->body(esther, selfObject, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3), Tuple_get(args, 4), Tuple_get(args, 5));

    case 7:
        return as_function(self)->body(esther, selfObject, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3), Tuple_get(args, 4), Tuple_get(args, 5), Tuple_get(args, 6));

    case 8:
        return as_function(self)->body(esther, selfObject, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3), Tuple_get(args, 4), Tuple_get(args, 5), Tuple_get(args, 6), Tuple_get(args, 7));

    case 9:
        return as_function(self)->body(esther, selfObject, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3), Tuple_get(args, 4), Tuple_get(args, 5), Tuple_get(args, 6), Tuple_get(args, 7), Tuple_get(args, 8));

    case 10:
        return as_function(self)->body(esther, selfObject, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3), Tuple_get(args, 4), Tuple_get(args, 5), Tuple_get(args, 6), Tuple_get(args, 7), Tuple_get(args, 8), Tuple_get(args, 9));

    case 11:
        return as_function(self)->body(esther, selfObject, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3), Tuple_get(args, 4), Tuple_get(args, 5), Tuple_get(args, 6), Tuple_get(args, 7), Tuple_get(args, 8), Tuple_get(args, 9), Tuple_get(args, 10));

    case 12:
        return as_function(self)->body(esther, selfObject, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3), Tuple_get(args, 4), Tuple_get(args, 5), Tuple_get(args, 6), Tuple_get(args, 7), Tuple_get(args, 8), Tuple_get(args, 9), Tuple_get(args, 10), Tuple_get(args, 11));

    case 13:
        return as_function(self)->body(esther, selfObject, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3), Tuple_get(args, 4), Tuple_get(args, 5), Tuple_get(args, 6), Tuple_get(args, 7), Tuple_get(args, 8), Tuple_get(args, 9), Tuple_get(args, 10), Tuple_get(args, 11), Tuple_get(args, 12));

    case 14:
        return as_function(self)->body(esther, selfObject, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3), Tuple_get(args, 4), Tuple_get(args, 5), Tuple_get(args, 6), Tuple_get(args, 7), Tuple_get(args, 8), Tuple_get(args, 9), Tuple_get(args, 10), Tuple_get(args, 11), Tuple_get(args, 12), Tuple_get(args, 13));

    case 15:
        return as_function(self)->body(esther, selfObject, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3), Tuple_get(args, 4), Tuple_get(args, 5), Tuple_get(args, 6), Tuple_get(args, 7), Tuple_get(args, 8), Tuple_get(args, 9), Tuple_get(args, 10), Tuple_get(args, 11), Tuple_get(args, 12), Tuple_get(args, 13), Tuple_get(args, 14));

    default:
        return NULL;
    }
}

Object *Function_virtual_toString(Esther *esther, Object *self) {
    const char *name = as_function(self)->name;

    if (strlen(name) == 0)
        return String_new(esther, "<anonymous function>");

    return String_new_std(esther, std_string_format("<function %s>", name));
}

static Object *InterpretedFunction_body(Esther *esther, InterpretedFunction *f, Object *self, Object *args) {
    Context *context = Context_childContext(f->closure, self, Object_new(esther));

    for (size_t i = 0; i < Tuple_size(args); i++)
        Context_setLocal(context, f->params[i], Tuple_get(args, i));

    return Esther_eval(esther, f->body, context);
}

Object *InterpretedFunction_new(Esther *esther, const char *name, int argc, const char **params, Context *closure, Object *body) {
    Object *self = malloc(sizeof(InterpretedFunction));

    Function_init(esther, self, name, InterpretedFunction_body, -2);

    as_interpretedFunction(self)->params = malloc(argc * sizeof(const char *));

    for (int i = 0; i < argc; i++)
        as_interpretedFunction(self)->params[i] = strdup(params[i]);

    as_interpretedFunction(self)->closure = closure;
    as_interpretedFunction(self)->body = body;

    return self;
}
