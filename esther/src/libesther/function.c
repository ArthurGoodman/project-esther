#include "esther/function.h"

#include <string.h>

#include "esther/array.h"
#include "esther/esther.h"
#include "esther/std_string.h"
#include "esther/string.h"
#include "esther/tuple.h"
#include "esther/context.h"

Object *Function_new(Esther *es, const char *name, Object *(*body)(), int argc) {
    Object *self = malloc(sizeof(Function));
    Function_init(es, self, name, body, argc);
    return self;
}

void Function_init(Esther *es, Object *self, const char *name, Object *(*body)(), int argc) {
    Object_init(es, self, es->functionClass);

    as_Function(self)->name = strdup(name);
    as_Function(self)->body = body;
    as_Function(self)->argc = argc;

    as_Function(self)->base.toString = Function_virtual_toString;
    as_Function(self)->base.inspect = Function_virtual_toString;
}

const char *Function_getName(Object *self) {
    return as_Function(self)->name;
}

Object *Function_invoke(Esther *es, Object *self, Object *selfObject, Object *args) {
    if (as_Function(self)->argc == -2)
        return as_Function(self)->body(es, self, selfObject, args);

    if (as_Function(self)->argc == -1)
        return as_Function(self)->body(es, selfObject, args);

    if (as_Function(self)->argc != (int)Tuple_size(args))
        return NULL;

    switch (as_Function(self)->argc) {
    case 0:
        return as_Function(self)->body(es, selfObject);

    case 1:
        return as_Function(self)->body(es, selfObject, Tuple_get(args, 0));

    case 2:
        return as_Function(self)->body(es, selfObject, Tuple_get(args, 0), Tuple_get(args, 1));

    case 3:
        return as_Function(self)->body(es, selfObject, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2));

    case 4:
        return as_Function(self)->body(es, selfObject, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3));

    case 5:
        return as_Function(self)->body(es, selfObject, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3), Tuple_get(args, 4));

    case 6:
        return as_Function(self)->body(es, selfObject, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3), Tuple_get(args, 4), Tuple_get(args, 5));

    case 7:
        return as_Function(self)->body(es, selfObject, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3), Tuple_get(args, 4), Tuple_get(args, 5), Tuple_get(args, 6));

    case 8:
        return as_Function(self)->body(es, selfObject, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3), Tuple_get(args, 4), Tuple_get(args, 5), Tuple_get(args, 6), Tuple_get(args, 7));

    case 9:
        return as_Function(self)->body(es, selfObject, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3), Tuple_get(args, 4), Tuple_get(args, 5), Tuple_get(args, 6), Tuple_get(args, 7), Tuple_get(args, 8));

    case 10:
        return as_Function(self)->body(es, selfObject, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3), Tuple_get(args, 4), Tuple_get(args, 5), Tuple_get(args, 6), Tuple_get(args, 7), Tuple_get(args, 8), Tuple_get(args, 9));

    case 11:
        return as_Function(self)->body(es, selfObject, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3), Tuple_get(args, 4), Tuple_get(args, 5), Tuple_get(args, 6), Tuple_get(args, 7), Tuple_get(args, 8), Tuple_get(args, 9), Tuple_get(args, 10));

    case 12:
        return as_Function(self)->body(es, selfObject, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3), Tuple_get(args, 4), Tuple_get(args, 5), Tuple_get(args, 6), Tuple_get(args, 7), Tuple_get(args, 8), Tuple_get(args, 9), Tuple_get(args, 10), Tuple_get(args, 11));

    case 13:
        return as_Function(self)->body(es, selfObject, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3), Tuple_get(args, 4), Tuple_get(args, 5), Tuple_get(args, 6), Tuple_get(args, 7), Tuple_get(args, 8), Tuple_get(args, 9), Tuple_get(args, 10), Tuple_get(args, 11), Tuple_get(args, 12));

    case 14:
        return as_Function(self)->body(es, selfObject, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3), Tuple_get(args, 4), Tuple_get(args, 5), Tuple_get(args, 6), Tuple_get(args, 7), Tuple_get(args, 8), Tuple_get(args, 9), Tuple_get(args, 10), Tuple_get(args, 11), Tuple_get(args, 12), Tuple_get(args, 13));

    case 15:
        return as_Function(self)->body(es, selfObject, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3), Tuple_get(args, 4), Tuple_get(args, 5), Tuple_get(args, 6), Tuple_get(args, 7), Tuple_get(args, 8), Tuple_get(args, 9), Tuple_get(args, 10), Tuple_get(args, 11), Tuple_get(args, 12), Tuple_get(args, 13), Tuple_get(args, 14));

    default:
        return NULL;
    }
}

Object *Function_virtual_toString(Esther *es, Object *self) {
    const char *name = as_Function(self)->name;

    if (strlen(name) == 0)
        return String_new(es, "<anonymous function>");

    return String_new_std(es, std_string_format("<function %s>", name));
}

static Object *InterpretedFunction_body(Esther *es, Object *self, Object *selfObject, Object *args) {
    Context *context = Context_childContext(as_InterpretedFunction(self)->closure, selfObject, Object_new(es));

    for (size_t i = 0; i < Tuple_size(args); i++)
        Context_setLocal(context, as_InterpretedFunction(self)->params[i], Tuple_get(args, i));

    return Esther_eval(es, as_InterpretedFunction(self)->body, context);
}

Object *InterpretedFunction_new(Esther *es, const char *name, Object *params, Context *closure, Object *body) {
    Object *self = malloc(sizeof(InterpretedFunction));
    InterpretedFunction_init(es, self, name, params, closure, body);
    return self;
}

void InterpretedFunction_init(Esther *es, Object *self, const char *name, Object *params, Context *closure, Object *body) {
    Function_init(es, self, name, InterpretedFunction_body, -2);

    int argc = Array_size(params);

    as_InterpretedFunction(self)->argc = argc;

    as_InterpretedFunction(self)->params = malloc(argc * sizeof(const char *));

    for (int i = 0; i < argc; i++)
        as_InterpretedFunction(self)->params[i] = strdup(String_c_str(Array_get(params, i)));

    as_InterpretedFunction(self)->closure = closure;
    as_InterpretedFunction(self)->body = body;
}
