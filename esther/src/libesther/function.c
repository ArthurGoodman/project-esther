#include "esther/function.h"

#include "esther/array.h"
#include "esther/context.h"
#include "esther/esther.h"
#include "esther/exception.h"
#include "esther/string.h"
#include "esther/tuple.h"

Object *Function_new(Esther *es, struct string name, Object *(*body)(), int argc) {
    Object *f = gc_alloc(sizeof(Function));
    Function_init(es, f, name, body, argc);
    return f;
}

static ObjectVTable vtable_for_Function = {
    .base = {
        .base = {
            .mapOnRefs = Object_virtual_mapOnRefs },
        .finalize = Function_virtual_finalize },
    .toString = Function_virtual_toString,
    .inspect = Function_virtual_toString,
    .equals = Object_virtual_equals,
    .less = Object_virtual_less,
    .isTrue = Object_virtual_isTrue,
    .clone = Object_virtual_clone_unimplemented
};

void Function_init(Esther *es, Object *f, struct string name, Object *(*body)(), int argc) {
    Object_init(es, f, TFunction, Esther_getRootObject(es, c_str_to_id("Function")));

    as_Function(f)->name = string_copy(name);
    as_Function(f)->body = body;
    as_Function(f)->argc = argc;

    *(void **) f = &vtable_for_Function;
}

struct string Function_getName(Object *f) {
    return as_Function(f)->name;
}

Object *Function_invoke(Esther *es, Object *f, Object *self, Object *args) {
    if (as_Function(f)->argc == -2)
        return as_Function(f)->body(es, f, self, args);

    if (as_Function(f)->argc == -1)
        return as_Function(f)->body(es, self, args);

    if (as_Function(f)->argc != (int) Tuple_size(args)) {
        Exception_throw_new(es, "invalid number of arguments");
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
    struct string name = as_Function(f)->name;

    if (name.size == 0)
        return String_new_c_str(es, "<anonymous function>");

    return String_new_move(es, string_format("<function %s>", name.data));
}

void Function_virtual_finalize(ManagedObject *self) {
    Object_virtual_finalize(self);

    string_free(as_Function(self)->name);
}

static Object *InterpretedFunction_body(Esther *es, Object *f, Object *self, Object *args) {
    if (as_InterpretedFunction(f)->argc != (int) Tuple_size(args)) {
        Exception_throw_new(es, "invalid number of arguments");
        return NULL;
    }

    Context *context = Context_childContext(as_InterpretedFunction(f)->closure, self, Object_new(es));

    for (size_t i = 0; i < Tuple_size(args); i++)
        Context_setLocal(context, str_to_id(as_InterpretedFunction(f)->params[i]), Tuple_get(args, i));

    return Esther_eval(es, as_InterpretedFunction(f)->body, context);
}

Object *InterpretedFunction_new(Esther *es, struct string name, Object *params, Context *closure, Object *body) {
    Object *f = gc_alloc(sizeof(InterpretedFunction));
    InterpretedFunction_init(es, f, name, params, closure, body);
    return f;
}

static ObjectVTable vtable_for_InterpretedFunction = {
    .base = {
        .base = {
            .mapOnRefs = InterpretedFunction_virtual_mapOnRefs },
        .finalize = InterpretedFunction_virtual_finalize },
    .toString = Function_virtual_toString,
    .inspect = Function_virtual_toString,
    .equals = Object_virtual_equals,
    .less = Object_virtual_less,
    .isTrue = Object_virtual_isTrue,
    .clone = Object_virtual_clone_unimplemented
};

void InterpretedFunction_init(Esther *es, Object *f, struct string name, Object *params, Context *closure, Object *body) {
    Function_init(es, f, name, InterpretedFunction_body, -2);

    int argc = Array_size(params);

    as_InterpretedFunction(f)->argc = argc;

    as_InterpretedFunction(f)->params = malloc(argc * sizeof(struct string));

    for (int i = 0; i < argc; i++)
        as_InterpretedFunction(f)->params[i] = string_copy(String_value(Array_get(params, i)));

    as_InterpretedFunction(f)->closure = closure;
    as_InterpretedFunction(f)->body = body;

    *(void **) f = &vtable_for_InterpretedFunction;
}

void InterpretedFunction_virtual_mapOnRefs(Mapper *self, MapFunction f) {
    Object_virtual_mapOnRefs(self, f);

    f(as_InterpretedFunction(self)->closure);
    f(as_InterpretedFunction(self)->body);
}

void InterpretedFunction_virtual_finalize(ManagedObject *self) {
    Function_virtual_finalize(self);

    for (int i = 0; i < as_InterpretedFunction(self)->argc; i++)
        string_free(as_InterpretedFunction(self)->params[i]);

    free(as_InterpretedFunction(self)->params);
}
