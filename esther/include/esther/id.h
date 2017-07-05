#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/common.h"

#ifdef __x86_64
typedef uint64_t Id;
#elif __i386
typedef uint32_t Id;
#endif

struct string *id_to_str(Id id);
Id str_to_id(const struct string *str);
Id c_str_to_id(const char *str);

#ifdef __cplusplus
}
#endif
