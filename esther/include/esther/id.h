#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/common.h"

typedef uint32_t Id;

const char *idToString(Id id);
Id stringToId(const char *str);

#ifdef __cplusplus
}
#endif
