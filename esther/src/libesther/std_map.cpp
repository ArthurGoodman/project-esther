#include "esther/std_map.h"

#include <map>
#include <string>

namespace {
typedef bool (*Compare)(void *, void *);

inline struct std_map *to_c(std::map<void *, void *, Compare> *ptr) {
    return reinterpret_cast<struct std_map *>(ptr);
}

inline std::map<void *, void *, Compare> *to_cpp(struct std_map *ptr) {
    return reinterpret_cast<std::map<void *, void *, Compare> *>(ptr);
}
}

struct std_map *std_map_new(bool (*compare)(void *, void *)) {
    return to_c(new std::map<void *, void *, Compare>(compare));
}

void std_map_delete(struct std_map *map) {
    delete to_cpp(map);
}

bool std_map_contains(struct std_map *map, const void *key) {
    return to_cpp(map)->find((void *)key) != to_cpp(map)->end();
}

void *std_map_get(struct std_map *map, const void *key) {
    return (*to_cpp(map))[(void *)key];
}

void std_map_set(struct std_map *map, const void *key, void *val) {
    (*to_cpp(map))[(void *)key] = val;
}
