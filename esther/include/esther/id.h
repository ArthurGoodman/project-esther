#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/common.h"

#ifdef __x86_64
typedef uint64_t ID;
#elif __i386
typedef uint32_t ID;
#endif

struct string id_to_str(ID id);
ID str_to_id(struct string str);
ID c_str_to_id(const char *str);

#ifdef __cplusplus
}
#endif
