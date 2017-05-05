#pragma once

#ifdef __cplusplus
extern "C" {
#endif

struct std_string;

struct std_string *read_file(const char *fileName);

#ifdef __cplusplus
}
#endif
