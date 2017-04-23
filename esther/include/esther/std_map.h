#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

struct std_map;

struct std_map *std_map_new(bool (*compare)(void *, void *));

void std_map_delete(struct std_map *map);

bool std_map_contains(struct std_map *map, const void *key);
void *std_map_get(struct std_map *map, const void *key);
void std_map_set(struct std_map *map, const void *key, void *val);

#ifdef __cplusplus
}
#endif
