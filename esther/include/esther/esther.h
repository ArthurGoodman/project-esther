#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/class.h"
#include "esther/id.h"
#include "esther/std_string.h"

typedef struct Context Context;

typedef struct Esther {
    Object *objectClass;
    Object *classClass;
    Object *stringClass;
    Object *symbolClass;
    Object *functionClass;
    Object *tupleClass;
    Object *arrayClass;
    Object *mapClass;
    Object *booleanClass;
    Object *nullClass;
    Object *numericClass;
    Object *charClass;
    Object *intClass;
    Object *floatClass;
    Object *exceptionClass;

    Object *trueObject;
    Object *falseObject;
    Object *nullObject;

    Object *lexer;
    Object *parser;

    Object *mainObject;
    Object *esther;
    Object *io;

    Context *root;

    Object *modules;

    struct std_map *rootObjects;

    struct FileRecord {
        const char *fileName;
        Object *source;
        struct FileRecord *next;
    } * file;
} Esther;

void Esther_init(Esther *es);
void Esther_finalize(Esther *es);

Object *Esther_toBoolean(Esther *es, bool value);

bool Esther_hasRootObject(Esther *es, ID name);
Object *Esther_getRootObject(Esther *es, ID name);
void Esther_setRootObject(Esther *es, ID name, Object *value);

Object *Esther_eval(Esther *es, Object *ast, Context *context);

void Esther_runScript(Esther *es, const char *fileName);
Object *Esther_runFile(Esther *es, const char *fileName);

Object *Esther_import(Esther *es, Context *context, const char *name);

#ifdef __cplusplus
}
#endif
