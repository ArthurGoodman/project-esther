#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

struct std_string_map;

struct std_string_map *std_string_map_new();

void std_string_map_delete(struct std_string_map *map);

bool std_string_map_contains(struct std_string_map *map, const char *key);
void *std_string_map_get(struct std_string_map *map, const char *key);
void std_string_map_set(struct std_string_map *map, const char *key, void *val);

#ifdef __cplusplus
}
#endif
