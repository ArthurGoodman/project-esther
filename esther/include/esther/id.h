#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/common.h"

#ifdef __x86_64
typedef uint64_t Id;
#else
typedef uint32_t Id;
#endif

const char *idToString(Id id);
Id stringToId(const char *str);

#ifdef __cplusplus
}
#endif
