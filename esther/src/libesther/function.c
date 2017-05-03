#include "esther/function.h"

#include <string.h>

#include "esther/array.h"
#include "esther/context.h"
#include "esther/esther.h"
#include "esther/exception.h"
#include "esther/std_string.h"
#include "esther/string.h"
#include "esther/tuple.h"

Object *Function_new(Esther *es, const char *name, Object *(*body)(), int argc) {
    Object *f = gc_alloc(sizeof(Function));
    Function_init(es, f, name, body, argc);
    return f;
}

void Function_init(Esther *es, Object *f, const char *name, Object *(*body)(), int argc) {
    Object_init(es, f, TFunction, es->functionClass);

    as_Function(f)->name = strdup(name);
    as_Function(f)->body = body;
    as_Function(f)->argc = argc;

    as_Function(f)->base.toString = Function_virtual_toString;
    as_Function(f)->base.inspect = Function_virtual_toString;

    f->base.finalize = Function_virtual_finalize;
}

const char *Function_getName(Object *f) {
    return as_Function(f)->name;
}

Object *Function_invoke(Esther *es, Object *f, Object *self, Object *args) {
    if (as_Function(f)->argc == -2)
        return as_Function(f)->body(es, f, self, args);

    if (as_Function(f)->argc == -1)
        return as_Function(f)->body(es, self, args);

    if (as_Function(f)->argc != (int)Tuple_size(args)) {
        Exception_throw(es, "invalid number of arguments");
        return NULL;
    }

    switch (as_Function(f)->argc) {
    case 0:
        return as_Function(f)->body(es, self);

    case 1:
        return as_Function(f)->body(es, self, Tuple_get(args, 0));

    case 2:
        return as_Function(f)->body(es, self, Tuple_get(args, 0), Tuple_get(args, 1));

    case 3:
        return as_Function(f)->body(es, self, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2));

    case 4:
        return as_Function(f)->body(es, self, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3));

    case 5:
        return as_Function(f)->body(es, self, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3), Tuple_get(args, 4));

    case 6:
        return as_Function(f)->body(es, self, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3), Tuple_get(args, 4), Tuple_get(args, 5));

    case 7:
        return as_Function(f)->body(es, self, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3), Tuple_get(args, 4), Tuple_get(args, 5), Tuple_get(args, 6));

    case 8:
        return as_Function(f)->body(es, self, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3), Tuple_get(args, 4), Tuple_get(args, 5), Tuple_get(args, 6), Tuple_get(args, 7));

    case 9:
        return as_Function(f)->body(es, self, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3), Tuple_get(args, 4), Tuple_get(args, 5), Tuple_get(args, 6), Tuple_get(args, 7), Tuple_get(args, 8));

    case 10:
        return as_Function(f)->body(es, self, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3), Tuple_get(args, 4), Tuple_get(args, 5), Tuple_get(args, 6), Tuple_get(args, 7), Tuple_get(args, 8), Tuple_get(args, 9));

    case 11:
        return as_Function(f)->body(es, self, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3), Tuple_get(args, 4), Tuple_get(args, 5), Tuple_get(args, 6), Tuple_get(args, 7), Tuple_get(args, 8), Tuple_get(args, 9), Tuple_get(args, 10));

    case 12:
        return as_Function(f)->body(es, self, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3), Tuple_get(args, 4), Tuple_get(args, 5), Tuple_get(args, 6), Tuple_get(args, 7), Tuple_get(args, 8), Tuple_get(args, 9), Tuple_get(args, 10), Tuple_get(args, 11));

    case 13:
        return as_Function(f)->body(es, self, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3), Tuple_get(args, 4), Tuple_get(args, 5), Tuple_get(args, 6), Tuple_get(args, 7), Tuple_get(args, 8), Tuple_get(args, 9), Tuple_get(args, 10), Tuple_get(args, 11), Tuple_get(args, 12));

    case 14:
        return as_Function(f)->body(es, self, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3), Tuple_get(args, 4), Tuple_get(args, 5), Tuple_get(args, 6), Tuple_get(args, 7), Tuple_get(args, 8), Tuple_get(args, 9), Tuple_get(args, 10), Tuple_get(args, 11), Tuple_get(args, 12), Tuple_get(args, 13));

    case 15:
        return as_Function(f)->body(es, self, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3), Tuple_get(args, 4), Tuple_get(args, 5), Tuple_get(args, 6), Tuple_get(args, 7), Tuple_get(args, 8), Tuple_get(args, 9), Tuple_get(args, 10), Tuple_get(args, 11), Tuple_get(args, 12), Tuple_get(args, 13), Tuple_get(args, 14));

    default:
        return NULL;
    }
}

Object *Function_virtual_toString(Esther *es, Object *f) {
    const char *name = as_Function(f)->name;

    if (strlen(name) == 0)
        return String_new(es, "<anonymous function>");

    return String_new_std(es, std_string_format("<function %s>", name));
}

void Function_virtual_finalize(ManagedObject *self) {
    Object_virtual_finalize(self);

    free((void *)as_Function(self)->name);
}

static Object *InterpretedFunction_body(Esther *es, Object *f, Object *self, Object *args) {
    if (as_InterpretedFunction(f)->argc != (int)Tuple_size(args)) {
        Exception_throw(es, "invalid number of arguments");
        return NULL;
    }

    Context *context = Context_childContext(as_InterpretedFunction(f)->closure, self, Object_new(es));

    for (size_t i = 0; i < Tuple_size(args); i++)
        Context_setLocal(context, as_InterpretedFunction(f)->params[i], Tuple_get(args, i));

    return Esther_eval(es, as_InterpretedFunction(f)->body, context);
}

Object *InterpretedFunction_new(Esther *es, const char *name, Object *params, Context *closure, Object *body) {
    Object *f = gc_alloc(sizeof(InterpretedFunction));
    InterpretedFunction_init(es, f, name, params, closure, body);
    return f;
}

void InterpretedFunction_init(Esther *es, Object *f, const char *name, Object *params, Context *closure, Object *body) {
    Function_init(es, f, name, InterpretedFunction_body, -2);

    int argc = Array_size(params);

    as_InterpretedFunction(f)->argc = argc;

    as_InterpretedFunction(f)->params = malloc(argc * sizeof(const char *));

    for (int i = 0; i < argc; i++)
        as_InterpretedFunction(f)->params[i] = strdup(String_c_str(Array_get(params, i)));

    as_InterpretedFunction(f)->closure = closure;
    as_InterpretedFunction(f)->body = body;

    f->base.base.mapOnReferences = InterpretedFunction_virtual_mapOnReferences;
    f->base.finalize = InterpretedFunction_virtual_finalize;
}

void InterpretedFunction_virtual_mapOnReferences(Mapper *self, MapFunction f) {
    Object_virtual_mapOnReferences(self, f);

    f((void **)&as_InterpretedFunction(self)->closure);
    f((void **)&as_InterpretedFunction(self)->body);
}

void InterpretedFunction_virtual_finalize(ManagedObject *self) {
    Function_virtual_finalize(self);

    for (size_t i = 0; i < as_InterpretedFunction(self)->argc; i++)
        free((void *)as_InterpretedFunction(self)->params[i]);

    free(as_InterpretedFunction(self)->params);
}
