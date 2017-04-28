#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/object.h"

#define X(a, b) extern Object *sym_##a;
#include "keywords.def"
#include "nodes.def"
#include "operators.def"
#include "othertokens.def"
#undef X

extern Object *keyword_symbols[];
extern Object *operator_symbols[];

void init_symbols(Esther *es);

#ifdef __cplusplus
}
#endif
