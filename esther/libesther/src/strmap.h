#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

struct strmap;

struct strmap *strmap_new();
void strmap_delete(struct strmap *map);

bool strmap_contains(struct strmap *map, const char *str);
void *strmap_get(struct strmap *map, const char *str);
void strmap_set(struct strmap *map, const char *str, void *val);

#ifdef __cplusplus
}
#endif
