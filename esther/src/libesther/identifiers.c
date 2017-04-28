#include "identifiers.h"

#define X(a, b) Id id_##a;
#include "keywords.def"
#include "nodes.def"
#include "operators.def"
#include "othertokens.def"
#undef X

void init_identifiers() {
#define X(a, b) id_##a = stringToId(b);
#include "keywords.def"
#include "nodes.def"
#include "operators.def"
#include "othertokens.def"
#undef X
}
