#include "esther/function.h"

#include "esther/esther.h"
#include "esther/tuple.h"

Function *Function_new(Esther *esther, Object *(*body)(), int argc) {
    Function *self = malloc(sizeof(Function));
    Function_init(esther, self, body, argc);
    return self;
}

void Function_init(Esther *esther, Function *self, Object *(*body)(), int argc) {
    Object_init(esther, &self->base, esther->functionClass);

    self->body = body;
    self->argc = argc;
}

Object *Function_invoke(Esther *esther, Function *self, Object *selfObject, Tuple *args) {
    Object *result = NULL;

    if (self->argc >= 0) {
        int argc = Tuple_size(args);

        for (int i = argc - 1; i >= 0; i--)
            asm("push %0"
                :
                : "g"(args->data[i]));

        asm("push %0\n"
            "push %1"
            :
            : "g"(selfObject), "g"(esther));

        result = self->body();

        asm("add %0, %%esp"
            :
            : "g"((argc + 2) * sizeof(Object *)));
    } else
        result = self->body(esther, selfObject, args);

    return result;
}
