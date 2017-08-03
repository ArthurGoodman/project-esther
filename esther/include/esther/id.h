#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "esther/std_string.h"

#if defined(__x86_64)
typedef uint64_t ID;
#elif defined(__i386)
typedef uint32_t ID;
#endif

bool is_valid_id(ID id);
struct string id_to_str(ID id);
ID str_to_id(struct string str);
ID cstr_to_id(const char *str);

#ifdef __cplusplus
}
#endif
