#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/object.h"
#include "esther/std_string.h"

typedef struct Context Context;

typedef struct Function {
    Object base;

    struct string name;
    Object *(*body)();
    int argc;
} Function;

#define as_Function(obj) ((Function *) (obj))

Object *Function_new(Esther *es, struct string name, Object *(*body)(), int argc);

void Function_init(Esther *es, Object *f, struct string name, Object *(*body)(), int argc);

struct string Function_getName(Object *f);

Object *Function_invoke(Esther *es, Object *f, Object *self, Object *args);

Object *Function_virtual_toString(Esther *es, Object *f);

void Function_virtual_finalize(ManagedObject *self);

typedef struct InterpretedFunction {
    Function base;

    int argc;
    struct string *params;
    Context *closure;
    Object *body;
} InterpretedFunction;

#define as_InterpretedFunction(obj) ((InterpretedFunction *) (obj))

Object *InterpretedFunction_new(Esther *es, struct string name, Object *params, Context *closure, Object *body);

void InterpretedFunction_init(Esther *es, Object *f, struct string name, Object *params, Context *closure, Object *body);

void InterpretedFunction_virtual_mapOnReferences(Mapper *self, MapFunction f);
void InterpretedFunction_virtual_finalize(ManagedObject *self);

#ifdef __cplusplus
}
#endif
