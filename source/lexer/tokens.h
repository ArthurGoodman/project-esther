#include "token.h"

enum {
    tNone = -1,

#define X(a, b) a,
#include "operators.def"
#include "keywords.def"
#undef X

#define X(a) a,
#include "othertokens.def"
#undef X

    tokensCount
};
