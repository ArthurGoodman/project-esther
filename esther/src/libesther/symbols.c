#include "symbols.h"

#include "esther/symbol.h"

#define X(a, b) Object *sym_##a;
#include "keywords.def"
#include "nodes.def"
#include "operators.def"
#include "othertokens.def"
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

void init_symbols(Esther *es) {
#define X(a, b) sym_##a = Symbol_new(es, b);
#include "keywords.def"
#include "nodes.def"
#include "operators.def"
#include "othertokens.def"
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
