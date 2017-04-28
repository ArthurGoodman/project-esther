#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/id.h"

#define X(a, b) extern Id id_##a;
#include "keywords.def"
#include "nodes.def"
#include "operators.def"
#include "othertokens.def"
#undef X

void init_identifiers();

#ifdef __cplusplus
}
#endif
