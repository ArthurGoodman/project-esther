#include "identifiers.h"

#include "esther/symbol.h"

#define X(a, b) \
    Id id_##a;  \
    Object *sym_##a;
#include "identifiers.def"
#include "keywords.def"
#include "operators.def"
#undef X

Object *keyword_symbols[] = {
#define X(a, b) NULL,
#include "keywords.def"
#undef X
};

Object *operator_symbols[] = {
#define X(a, b) NULL,
#include "operators.def"
#undef X
};

void init_identifiers(Esther *es) {
#define X(a, b)             \
    id_##a = stringToId(b); \
    sym_##a = Symbol_new(es, b);
#include "identifiers.def"
#include "keywords.def"
#include "operators.def"
#undef X

    int i = 0;

#define X(a, b) keyword_symbols[i++] = sym_##a;
#include "keywords.def"
#undef X

    i = 0;

#define X(a, b) operator_symbols[i++] = sym_##a;
#include "operators.def"
#undef X
}
