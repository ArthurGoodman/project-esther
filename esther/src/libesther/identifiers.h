#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/id.h"

typedef struct Object Object;
typedef struct Esther Esther;

#define X(a, b)       \
    extern ID id_##a; \
    extern Object *sym_##a;
#include "identifiers.def"
#include "keywords.def"
#include "operators.def"
#undef X

extern Object *keyword_symbols[];
extern Object *operator_symbols[];

void init_identifiers(Esther *es);

#ifdef __cplusplus
}
#endif
