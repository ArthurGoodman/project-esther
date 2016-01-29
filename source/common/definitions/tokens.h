#pragma once

enum {
    tNone = -1,

#define X(a, b) a,
#include "operators.def"
#include "keywords.def"
#include "othertokens.def"
#undef X
};
