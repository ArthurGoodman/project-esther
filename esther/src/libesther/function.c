#include "esther/function.h"

#include <string.h>

#include "esther/esther.h"
#include "esther/std_string.h"
#include "esther/string.h"
#include "esther/tuple.h"
#include "esther/context.h"

Function *Function_new(Esther *esther, const char *name, Object *(*body)(), int argc) {
    Function *self = malloc(sizeof(Function));
    Function_init(esther, self, name, body, argc);
    return self;
}

void Function_init(Esther *esther, Function *self, const char *name, Object *(*body)(), int argc) {
    Object_init(esther, &self->base, esther->functionClass);

    self->name = strdup(name);
    self->body = body;
    self->argc = argc;

    self->base.toString = Function_virtual_toString;
    self->base.inspect = Function_virtual_toString;
}

const char *Function_getName(Function *self) {
    return self->name;
}

Object *Function_invoke(Esther *esther, Function *self, Object *selfObject, Tuple *args) {
    if (self->argc == -2)
        return self->body(esther, self, selfObject, args);

    if (self->argc == -1)
        return self->body(esther, selfObject, args);

    if (self->argc != (int)Tuple_size(args))
        return NULL;

    switch (self->argc) {
    case 0:
        return self->body(esther, selfObject);

    case 1:
        return self->body(esther, selfObject, Tuple_get(args, 0));

    case 2:
        return self->body(esther, selfObject, Tuple_get(args, 0), Tuple_get(args, 1));

    case 3:
        return self->body(esther, selfObject, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2));

    case 4:
        return self->body(esther, selfObject, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3));

    case 5:
        return self->body(esther, selfObject, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3), Tuple_get(args, 4));

    case 6:
        return self->body(esther, selfObject, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3), Tuple_get(args, 4), Tuple_get(args, 5));

    case 7:
        return self->body(esther, selfObject, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3), Tuple_get(args, 4), Tuple_get(args, 5), Tuple_get(args, 6));

    case 8:
        return self->body(esther, selfObject, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3), Tuple_get(args, 4), Tuple_get(args, 5), Tuple_get(args, 6), Tuple_get(args, 7));

    case 9:
        return self->body(esther, selfObject, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3), Tuple_get(args, 4), Tuple_get(args, 5), Tuple_get(args, 6), Tuple_get(args, 7), Tuple_get(args, 8));

    case 10:
        return self->body(esther, selfObject, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3), Tuple_get(args, 4), Tuple_get(args, 5), Tuple_get(args, 6), Tuple_get(args, 7), Tuple_get(args, 8), Tuple_get(args, 9));

    case 11:
        return self->body(esther, selfObject, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3), Tuple_get(args, 4), Tuple_get(args, 5), Tuple_get(args, 6), Tuple_get(args, 7), Tuple_get(args, 8), Tuple_get(args, 9), Tuple_get(args, 10));

    case 12:
        return self->body(esther, selfObject, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3), Tuple_get(args, 4), Tuple_get(args, 5), Tuple_get(args, 6), Tuple_get(args, 7), Tuple_get(args, 8), Tuple_get(args, 9), Tuple_get(args, 10), Tuple_get(args, 11));

    case 13:
        return self->body(esther, selfObject, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3), Tuple_get(args, 4), Tuple_get(args, 5), Tuple_get(args, 6), Tuple_get(args, 7), Tuple_get(args, 8), Tuple_get(args, 9), Tuple_get(args, 10), Tuple_get(args, 11), Tuple_get(args, 12));

    case 14:
        return self->body(esther, selfObject, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3), Tuple_get(args, 4), Tuple_get(args, 5), Tuple_get(args, 6), Tuple_get(args, 7), Tuple_get(args, 8), Tuple_get(args, 9), Tuple_get(args, 10), Tuple_get(args, 11), Tuple_get(args, 12), Tuple_get(args, 13));

    case 15:
        return self->body(esther, selfObject, Tuple_get(args, 0), Tuple_get(args, 1), Tuple_get(args, 2), Tuple_get(args, 3), Tuple_get(args, 4), Tuple_get(args, 5), Tuple_get(args, 6), Tuple_get(args, 7), Tuple_get(args, 8), Tuple_get(args, 9), Tuple_get(args, 10), Tuple_get(args, 11), Tuple_get(args, 12), Tuple_get(args, 13), Tuple_get(args, 14));

    default:
        return NULL;
    }
}

String *Function_virtual_toString(Esther *esther, Object *self) {
    const char *name = ((Function *)self)->name;

    if (strlen(name) == 0)
        return String_new(esther, "<anonymous function>");

    return String_new_std(esther, std_string_format("<function %s>", name));
}

static Object *InterpretedFunction_body(Esther *esther, InterpretedFunction *f, Object *self, Tuple *args) {
    Context *context = Context_childContext(f->closure, self, Object_new(esther));

    for (size_t i = 0; i < Tuple_size(args); i++)
        Context_setLocal(context, f->params[i], Tuple_get(args, i));

    return Esther_eval(esther, f->body, context);
}

Function *InterpretedFunction_new(Esther *esther, const char *name, int argc, const char **params, Context *closure, Object *body) {
    InterpretedFunction *self = malloc(sizeof(InterpretedFunction));

    Function_init(esther, &self->base, name, InterpretedFunction_body, -2);

    self->params = malloc(argc * sizeof(const char *));

    for (int i = 0; i < argc; i++)
        self->params[i] = strdup(params[i]);

    self->closure = closure;
    self->body = body;

    return (Function *)self;
}
