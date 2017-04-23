#include "esther/function.h"

#include <string.h>

#include "esther/esther.h"
#include "esther/tuple.h"
#include "esther/std_string.h"
#include "esther/string.h"

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
}

const char *Function_getName(Function *self) {
    return self->name;
}

Object *Function_invoke(Esther *esther, Function *self, Object *selfObject, Tuple *args) {
    if (self->argc < 0)
        return self->body(esther, selfObject, args);

    size_t argc = Tuple_size(args);

    for (int i = argc - 1; i >= 0; i--)
        asm("push %0"
            :
            : "g"(args->data[i]));

    asm("push %0\n"
        "push %1"
        :
        : "g"(selfObject), "g"(esther));

    Object *result = self->body();

    asm("add %0, %%esp"
        :
        : "g"((argc + 2) * sizeof(Object *)));

    return result;
}

String *Function_virtual_toString(Esther *esther, Object *self) {
    const char *name = ((Function *)self)->name;

    if (strlen(name) == 0)
        return String_new_init(esther, "<anonymous function>");

    return String_new_init_std(esther, std_string_format("<function %s>", name));
}
