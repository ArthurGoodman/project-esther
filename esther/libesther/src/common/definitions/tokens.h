#pragma once

namespace es {

enum {
    tNone = -1,

#define X(a, b) a,
#include "common/definitions/operators.def"
#include "common/definitions/keywords.def"
#include "common/definitions/othertokens.def"
#undef X
};
}
