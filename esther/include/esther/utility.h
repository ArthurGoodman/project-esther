#pragma once

#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

struct string vformat(const char *fmt, va_list ap);

#ifdef __cplusplus
}
#endif
