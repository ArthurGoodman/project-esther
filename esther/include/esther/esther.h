#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/class.h"

typedef struct Context Context;

typedef struct Esther {
    Object *objectClass;
    Object *classClass;
    Object *stringClass;
    Object *symbolClass;
    Object *functionClass;
    Object *tupleClass;
    Object *arrayClass;
    Object *booleanClass;
    Object *nullClass;
    Object *numericClass;
    Object *charClass;
    Object *intClass;
    Object *floatClass;

    Object *trueObject;
    Object *falseObject;
    Object *nullObject;

    Object *mainObject;
    Object *io;

    Context *root;

    struct std_map *rootObjects;
} Esther;

void Esther_init(Esther *self);

Object *Esther_toBoolean(Esther *self, bool value);

bool Esther_hasRootObject(Esther *self, const char *name);
Object *Esther_getRootObject(Esther *self, const char *name);
void Esther_setRootObject(Esther *self, const char *name, Object *value);

Object *Esther_eval(Esther *self, Object *ast, Context *context);

#ifdef __cplusplus
}
#endif
