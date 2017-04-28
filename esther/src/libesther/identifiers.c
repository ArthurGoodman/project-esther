#include "identifiers.h"

#define X(a, b) Id id_##a;
#include "identifiers.def"
#undef X

void init_identifiers() {
#define X(a, b) id_##a = stringToId(b);
#include "identifiers.def"
#undef X
}
