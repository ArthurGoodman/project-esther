#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/object.h"

typedef struct Context Context;

typedef struct Esther {
    Mapper *globalMapper;

    Object *trueObject;
    Object *falseObject;
    Object *nullObject;

    Object *lexer;
    Object *parser;

    Object *mainObject;
    Object *esther;

    Context *root;

    Object *modules;

    struct std_map *rootObjects;

    struct FileRecord {
        const char *fileName;
        Object *source;
        struct FileRecord *next;
    } * file;

    struct std_map *moduleHandles;
} Esther;

void Esther_init(Esther *es);
void Esther_finalize(Esther *es);

Object *Esther_toBoolean(Esther *es, bool value);

bool Esther_hasRootObject(Esther *es, ID name);
Object *Esther_getRootObject(Esther *es, ID name);
void Esther_setRootObject(Esther *es, ID name, Object *value);

Object *Esther_eval(Esther *es, Object *ast, Context *context);

void Esther_runScript(Esther *es, const char *fileName);
Object *Esther_evalFile(Esther *es, const char *fileName);

Object *Esther_importModule(Esther *es, Context *context, const char *name);
void Esther_unloadModule(Esther *es, const char *name, void *library);

#ifdef __cplusplus
}
#endif
