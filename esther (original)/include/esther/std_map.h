#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

struct std_map;

#ifdef __x86_64
typedef uint64_t std_map_iterator;
#elif __i386
typedef uint32_t std_map_iterator;
#endif

typedef bool (*Compare)(void *, void *);

struct std_map *std_map_new(Compare compare);

void std_map_delete(struct std_map *map);

bool std_map_contains(struct std_map *map, const void *key);
void *std_map_get(struct std_map *map, const void *key);
void std_map_set(struct std_map *map, const void *key, void *value);

void std_map_begin(struct std_map *map, std_map_iterator *i);
bool std_map_end(struct std_map *map, std_map_iterator *i);

void *std_map_iterator_key(std_map_iterator *i);
void *std_map_iterator_value(std_map_iterator *i);

void std_map_iterator_set_value(std_map_iterator *i, void *value);

void std_map_iterator_next(std_map_iterator *i);

#ifdef __cplusplus
}
#endif
